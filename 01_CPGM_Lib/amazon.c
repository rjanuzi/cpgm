#include <amazon.h>

pgm_img_t amz_applyMediaNTimes(char* inputImgPath, int times)
{
	pgm_img_t pgmImg1, pgmImageResult;
	mtx_matrixFloat_t mask;
	int i;

	mask = flt_getMeanMask();

	pgmImg1 = pgm_createImg(inputImgPath);

	pgmImageResult = pgm_applyMaskFloat(pgmImg1, mask);

	for(i = 1; i < times; i++)
	{
		pgm_destroyPgm(pgmImg1);
		pgmImg1 = pgm_cpyImg(pgmImageResult);
		pgm_destroyPgm(pgmImageResult);
		pgmImageResult = pgm_applyMaskFloat(pgmImg1, mask);
	}

	pgm_destroyPgm(pgmImg1);

	return pgmImageResult;
}

pgm_img_t amz_applyMaxNTimes(char* inputImgPath, int times)
{
	pgm_img_t pgmImg1, pgmImageResult;
	mtx_matrixFloat_t mask;
	int i;

	mask = flt_getMeanMask();

	pgmImg1 = pgm_createImg(inputImgPath);

	pgmImageResult = pgm_applyMaxMask(pgmImg1);

	for(i = 1; i < times; i++)
	{
		pgm_destroyPgm(pgmImg1);
		pgmImg1 = pgm_cpyImg(pgmImageResult);
		pgm_destroyPgm(pgmImageResult);
		pgmImageResult = pgm_applyMaxMask(pgmImg1);
	}

	pgm_destroyPgm(pgmImg1);

	return pgmImageResult;
}

pgm_img_t amz_preProcessImg(char* inputImgPath, int masksCount)
{
	pgm_img_t resultImg;

	resultImg = amz_applyMaxNTimes(inputImgPath, masksCount);
	pgm_savePgmImg(resultImg, "C:\\Users\\Rafael\\Desktop\\result.pgm");
	pgm_destroyPgm(resultImg);

	resultImg = amz_applyMediaNTimes("C:\\Users\\Rafael\\Desktop\\result.pgm", masksCount);
	pgm_savePgmImg(resultImg, "C:\\Users\\Rafael\\Desktop\\result.pgm");
	pgm_destroyPgm(resultImg);

	resultImg = amz_applyMaxNTimes("C:\\Users\\Rafael\\Desktop\\result.pgm", masksCount);
	pgm_savePgmImg(resultImg, "C:\\Users\\Rafael\\Desktop\\result.pgm");
	pgm_destroyPgm(resultImg);

	resultImg = amz_applyMediaNTimes("C:\\Users\\Rafael\\Desktop\\result.pgm", masksCount);
	pgm_savePgmImg(resultImg, "C:\\Users\\Rafael\\Desktop\\result.pgm");

	return resultImg;
}

pgm_img_t amz_blackForestRegions(pgm_img_t inputImg, int limiar)
{
	pgm_img_t resultantImg = pgm_createEmptyImg(inputImg.imgMatrix.nLines, inputImg.imgMatrix.nCols);
	mtx_pos_t* vizinhos;
	mtx_pos_t actualPos;
	int i, j, k, m, n, nVizinhos = 8, media;
	mtx_matrixFloat_t mask;

	mask = flt_getMeanMask();

	for(i = 0; i < resultantImg.imgMatrix.nLines; i++)
	{
		printf("\nAplicando mascara... %.2f%c", ( ((float)i)/ ((float)resultantImg.imgMatrix.nLines)) * 100.0, '%');

		for(j = 0; j < resultantImg.imgMatrix.nCols; j++)
		{
			actualPos.lineIndex = i;
			actualPos.colIndex = j;
			vizinhos = mtx_getVizinhos8(actualPos, resultantImg.imgMatrix.nLines-1, resultantImg.imgMatrix.nCols-1);

			/* Primeiro calcula usando o centro da mascara. (pixel * w11) */
			media = (inputImg.imgMatrix.mtx[i][j] * mask.mtx[1][1]);

			/* Agora calcula para o resto dos vizinhos 8 (pixel_vk * w_mn) */
			k = 0;
			for(m = 0; m < 3; m++)
				for(n = 0; n < 3; n++)
				{
					if( m == 1 && n == 1) /* Tem que considerar o proprio pixel e nao um vizinho. */
					{
						media += (inputImg.imgMatrix.mtx[i][j] * mask.mtx[m][n]);
					}
					else /* Calcula a mascara usando os vizinhos */
					{
						/* Se tenho vizinho nessa posicao do pixel usa. */
						if(vizinhos[k].lineIndex >= 0 && vizinhos[k].colIndex >= 0)
						{
							media += (inputImg.imgMatrix.mtx[vizinhos[k].lineIndex][vizinhos[k].colIndex] * \
									mask.mtx[m][n]);
						}

						/* Tendo ou nao vizinho vai para o proximo. */
						k++;
					}
				}

			/* Se o valor do pixel for diferente da media em relacao ao limiar coloca 0 (preto) */
			if(media > inputImg.imgMatrix.mtx[i][j])
			{
				if((media - inputImg.imgMatrix.mtx[i][j]) > limiar)
					resultantImg.imgMatrix.mtx[i][j] = 0;
				else
					resultantImg.imgMatrix.mtx[i][j] = inputImg.imgMatrix.mtx[i][j];
			}
			else
			{
				if((inputImg.imgMatrix.mtx[i][j] - media) > limiar)
					resultantImg.imgMatrix.mtx[i][j] = 0;
				else
					resultantImg.imgMatrix.mtx[i][j] = inputImg.imgMatrix.mtx[i][j];
			}

			free(vizinhos);
		}
	}

	return resultantImg;
}

pgm_img_t amz_blackForestRegions2(pgm_img_t inputImg, int limiar, int blockSize)
{
	pgm_img_t resultantImg = pgm_createEmptyImg(inputImg.imgMatrix.nLines, inputImg.imgMatrix.nCols);
	int beginI, endI, beginJ, endJ, i, j, k, l, m, blockPxlCount = 255;
	double pArray[256]; /* Valor de densidade de probabilidade para o pixel com intensidade i */
	uint32_t pixelIntensidadeCount[256]; /* Frequencia de aparicoes do pixel i */
	double hAux, aux; /* Entropia do bloco corrente */
	FILE* fileToSave;

	/* Para cada bloco na imagem completa */
	for(k = 0; k < inputImg.imgMatrix.nLines; k += blockSize)
	{
		for(l = 0; l < inputImg.imgMatrix.nCols; l += blockSize)
		{
			beginI = k;
			endI = k + blockSize;
			beginJ = l;
			endJ = l + blockSize;

			/* Limpa array de frequencias de aparicoes */
			for(m = 0; m < 256; m++)
				pixelIntensidadeCount[m] = 0.0;

			/* Para todo o bloco atual calcula a entropia*/
			for(i = beginI; i < endI && i < inputImg.imgMatrix.nLines; i++)
				for(j = beginJ; j < endJ && j < inputImg.imgMatrix.nCols; j++)
					pixelIntensidadeCount[inputImg.imgMatrix.mtx[i][j]]++; /* Ni */

			/* Calculando a densidade de probabilidade de cada pixel */
//			blockPxlCount = i*j; /* Precisa da conta, pois o bloco pode não tem o tamanho exatamente como o previsto (limites) */
			for(m = 0; m < 256; m++)
			{
				pArray[m] = ((double)pixelIntensidadeCount[m]) / ((double)blockPxlCount); /* Pi = Ni/n */
				printf("\npArray[%d]: %.5f = %lu / %d", m, pArray[m], pixelIntensidadeCount[m], blockPxlCount);
			}

			/* Calcula a entropia */
			hAux = 0.0; /* - SUM( Pi * log2(Pi) ) */
			for(m = 0; m < 256; m++)
				hAux += (pArray[m] * log2(pArray[m]));
			hAux = -hAux;

			/* ======================================================================= */
			fileToSave = fopen("entropias.txt","a");
			fprintf(fileToSave, "\n%.5f", hAux);
			fclose(fileToSave);
			/* ======================================================================= */

			/* Ainda para o bloco sendo avaliado decide qual cor ele terah. */
			if(hAux > limiar)
				for(i = beginI; i < endI && i < inputImg.imgMatrix.nLines; i++)
					for(j = beginJ; j < endJ && j < inputImg.imgMatrix.nCols; j++)
					{
						resultantImg.imgMatrix.mtx[i][j] = 255;
					}
			else
				for(i = beginI; i < endI && i < inputImg.imgMatrix.nLines; i++)
					for(j = beginJ; j < endJ && j < inputImg.imgMatrix.nCols; j++)
					{
						resultantImg.imgMatrix.mtx[i][j] = 255;
					}
		}
	}

	return resultantImg;
}

//double log2( double n )
//{
//    // log(n)/log(2) is log2.
//    return log( n ) / log( 2 );
//}
