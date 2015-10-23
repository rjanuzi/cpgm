#include <pgm.h>

pgm_img_t pgm_createImg(const char* pgmFilePath)
{
	int fscanfResultAux, i, j, nLinesTemp, nColsTemp;
	long k;
	char stringAux[100];
	uint16_t intAux;
	pgm_img_t createdPgmImg;
	FILE* pgmFile;
	bool pgmInASCII = false;
	bool temComentario = false;

	createdPgmImg.isOk = false; /* Apenas se torna true se tudo estiver correto ao final. */

	/* Abrindo o arquivo */
	pgmFile = fopen(pgmFilePath, "r");

	if( pgmFile == NULL )
	{
		printf("\nERRO - pgm_createImg: Erro na abertura da imagem: %s", pgmFilePath);
		return createdPgmImg; /* Termina o programa. */
	}

	/* Lendo o cabecalho */
	fscanfResultAux = fscanf(pgmFile, "%s", stringAux);
	/* A primeira coisa no deve ser a string "P2" (Magic Code) */
	if( fscanfResultAux == 0 )
	{
		printf("\npgm_createImg - ERRO: Header PGM invalido.");
		return createdPgmImg;
	}
	else
	{
		if(strcmp(stringAux, PGM_MAGIC_CODE_ASCII) == 0)
			pgmInASCII = true;
		else
			if(strcmp(stringAux, PGM_MAGIC_CODE_BIN) == 0)
				pgmInASCII = false;
			else
			{
				printf("\npgm_createImg - ERRO: Magic CODE invalido: %s", stringAux);
				return createdPgmImg;
			}

	}

	/* Pula texto TODO Melhorar esse Skip do comentario. */
	while( fscanf(pgmFile, "%s", stringAux) != EOF  )
	{
		if(strcmp(stringAux, "#") == 0)
			temComentario = true;

		/* O loop para (break) quando encotra uma string que pode ser convertida para um inteiro
		 * no caso de imagens pgm convertidas usando o GIMP eh a versao do filtro. */
		intAux = atoi(stringAux);
		if(intAux != 0)
			break;
	}
	if( fscanfResultAux == EOF )
	{
		printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta. 1");
		return createdPgmImg;
	}

	if(!temComentario)
		nColsTemp = intAux; /* Se nao tiver comentario a string lida eh o numero de colunas. */
	else
	{
		/* Se tiver comentario, precisa ler o numero de colunas agora. */
		/* Recupera numero de cols */
		if((fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
			nColsTemp= intAux;
		else
		{
			printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta. 2");
			return createdPgmImg;
		}
	}

	/* Recupera numero de linhas */
	if((fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		nLinesTemp = intAux;
	else
	{
		printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta. 3");
		return createdPgmImg;
	}

	/* Recupera numero valor maximo */
	if((fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		createdPgmImg.maxValue = intAux;
	else
	{
		printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta. 4");
		return createdPgmImg;
	}

	if(pgmInASCII)
	{
		i = 0;
		j = 0;
		/* Recupera a matriz */
		createdPgmImg.imgMatrix = mtx_createMatrixS16(nLinesTemp, nColsTemp);

		while( (fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		{
			createdPgmImg.imgMatrix.mtx[i][j] = intAux;
			j++;
			if( j >= nColsTemp )
			{
				j = 0;
				i++;
			}
		}

		createdPgmImg.isOk = true;
	}
	else
	{
		i = 0;
		j = 0;
		uint8_t auxData;
		long x;
		long size = nLinesTemp*nColsTemp;
		/* Recupera a matriz */
		createdPgmImg.imgMatrix = mtx_createMatrixS16(nLinesTemp, nColsTemp);
		for(k = 0; k < size; k++)
		{
			if(fread((void*)&auxData, 1, 1, pgmFile) == 0)
			{
				printf("ERRO - pgm_createImg: fread leu 0 bytes.");
				break;
			}

			createdPgmImg.imgMatrix.mtx[i][j] = auxData;
			j++;
			if( j >= nColsTemp )
			{
				j = 0;
				i++;
			}
		}

		createdPgmImg.isOk = true;
	}

	fclose(pgmFile);

	return createdPgmImg;
}

pgm_img_t pgm_createEmptyImg(int nLines, int nCols)
{
	pgm_img_t newPgmImage;

	newPgmImage.maxValue = PGM_PIXEL_MAX_VALUE;
	newPgmImage.imgMatrix = mtx_createMatrixS16(nLines, nCols);
	if(newPgmImage.imgMatrix.mtx != NULL)
		newPgmImage.isOk = true;
	else
		newPgmImage.isOk = false;

	return newPgmImage;
}

void pgm_destroyPgm(pgm_img_t pgmImgToDestroy)
{
	pgmImgToDestroy.isOk = false;
	pgmImgToDestroy.maxValue = 0;
	mtx_freeMatrixS16(pgmImgToDestroy.imgMatrix);
}

void pgm_savePgmImg(pgm_img_t pgmImgToSave, const char* fileName)
{
	FILE* fileToSave = fopen(fileName, "w");
	int i,j;

	if( fileToSave == NULL )
	{
		printf("\nERRO - pgm_savePgmImg: fileToSave == NULL", fileToSave);
		return; /* Termina o programa. */
	}

	//	fprintf(fileToSave, PGM_MAGIC_CODE_BIN);
	fprintf(fileToSave, PGM_MAGIC_CODE_ASCII);
	fprintf(fileToSave, "\n");
	fprintf(fileToSave, "# Arquivo criado com a biblioteca cpgm Version 1.0\n");
	fprintf(fileToSave, "%d %d\n", pgmImgToSave.imgMatrix.nCols, pgmImgToSave.imgMatrix.nLines);
	fprintf(fileToSave, "%d\n", pgmImgToSave.maxValue);

	for(i = 0; i < pgmImgToSave.imgMatrix.nLines; i++)
		for(j = 0; j < pgmImgToSave.imgMatrix.nCols; j++)
			//			fwrite((void*)&pgmImgToSave.imgMatrix.mtx[i][j], 1, 1, fileToSave);
			fprintf(fileToSave, "%d\n", pgmImgToSave.imgMatrix.mtx[i][j]);

	fclose(fileToSave);
}

void pgm_sumScalar(pgm_img_t pgmInputImg, int scalarToSum)
{
	mtx_sumScalarS16(pgmInputImg.imgMatrix, scalarToSum);
}

pgm_img_t pgm_diff(pgm_img_t pgmL, pgm_img_t pgmR)
{
	pgm_img_t resultImg;

	resultImg.imgMatrix = mtx_subMatrixS16(pgmL.imgMatrix, pgmR.imgMatrix);
	resultImg.maxValue = pgmL.maxValue;

	if(resultImg.imgMatrix.mtx != NULL)
		resultImg.isOk = true;
	else
		resultImg.isOk = false;

	return resultImg;
}

pgm_img_t pgm_diffLim(pgm_img_t pgmL, pgm_img_t pgmR, int valorLimiar)
{
	pgm_img_t resultImg;
	int i,j;

	resultImg.imgMatrix = mtx_subMatrixS16(pgmL.imgMatrix, pgmR.imgMatrix);
	resultImg.maxValue = pgmL.maxValue;

	if(resultImg.imgMatrix.mtx != NULL)
	{
		resultImg.isOk = true;
		for(i = 0; i < resultImg.imgMatrix.nLines; i++)
			for(j = 0; j < resultImg.imgMatrix.nCols; j++)
				if( resultImg.imgMatrix.mtx[i][j] > valorLimiar )
					resultImg.imgMatrix.mtx[i][j] = 255;
				else
					resultImg.imgMatrix.mtx[i][j] = 0;
	}
	else
		resultImg.isOk = false;

	return resultImg;
}

pgm_img_t pgm_findMaskInImagePaP(pgm_img_t pgmImg, mtx_matrixS16_t mask, uint8_t limiarDeDiferenca)
{
	pgm_img_t resultImg;
	mtx_matrixS16_t blocoSendoAvaliado;
	bool wallyIsInActualBlock = false;
	int i, j, relativeI, relativeJ, maxRelativeI, maxRelativeJ;

	resultImg = pgm_createEmptyImg(pgmImg.imgMatrix.nLines, pgmImg.imgMatrix.nCols);
	resultImg.maxValue = pgmImg.maxValue;

	maxRelativeI = pgmImg.imgMatrix.nLines-mask.nLines;
	maxRelativeJ = pgmImg.imgMatrix.nCols-mask.nCols;

	for(relativeI = 0; relativeI <= maxRelativeI; relativeI++){
		printf("\nRunning... %.2f%c", (((float)relativeI)/((float)maxRelativeI))*100.0,'%');
		for(relativeJ = 0; relativeJ <= maxRelativeJ; relativeJ++)
		{
			blocoSendoAvaliado = mtx_createMatrixS16(mask.nLines, mask.nCols);

			/* Copia um bloco da imagem original para matrixAux. */
			for(i = 0; i < blocoSendoAvaliado.nLines; i++)
				for(j = 0; j < blocoSendoAvaliado.nCols; j++)
					blocoSendoAvaliado.mtx[i][j] = pgmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];

			/* Verifica se o wally estah no bloco da imagem sendo analisada */
			wallyIsInActualBlock = mtx_equalsPaP(blocoSendoAvaliado, mask, limiarDeDiferenca);

			/* Caso um wally tenha sido encontrado na posicao avaliada,
			 * desenha o que encontrou na imagem de resultado */
			if(wallyIsInActualBlock)
			{
				for(i = 0; i < mask.nLines; i++)
					for(j = 0; j < mask.nCols; j++)
						resultImg.imgMatrix.mtx[relativeI+i][relativeJ+j] = pgmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
			}

			mtx_freeMatrixS16(blocoSendoAvaliado);
		}
	}

	return resultImg;
}

pgm_img_t pgm_findMaskInImageMean(pgm_img_t pgmImg, mtx_matrixS16_t mask, uint8_t limiarDeDiferenca)
{
	pgm_img_t resultImg;
	mtx_matrixS16_t blocoSendoAvaliado;
	bool wallyIsInActualBlock = false;
	int i, j, relativeI, relativeJ, maxRelativeI, maxRelativeJ;

	resultImg = pgm_createEmptyImg(pgmImg.imgMatrix.nLines, pgmImg.imgMatrix.nCols);
	resultImg.maxValue = pgmImg.maxValue;

	maxRelativeI = pgmImg.imgMatrix.nLines-mask.nLines;
	maxRelativeJ = pgmImg.imgMatrix.nCols-mask.nCols;

	for(relativeI = 0; relativeI <= maxRelativeI; relativeI++){
		printf("\nRunning... %.2f%c", (((float)relativeI)/((float)maxRelativeI))*100.0,'%');
		for(relativeJ = 0; relativeJ <= maxRelativeJ; relativeJ++)
		{
			blocoSendoAvaliado = mtx_createMatrixS16(mask.nLines, mask.nCols);

			/* Copia um bloco da imagem original para matrixAux. */
			for(i = 0; i < blocoSendoAvaliado.nLines; i++)
				for(j = 0; j < blocoSendoAvaliado.nCols; j++)
					blocoSendoAvaliado.mtx[i][j] = pgmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];

			/* Verifica se o wally estah no bloco da imagem sendo analisada */
			wallyIsInActualBlock = mtx_equalsMean(blocoSendoAvaliado, mask, limiarDeDiferenca);

			/* Caso um wally tenha sido encontrado na posicao avaliada,
			 * desenha o que encontrou na imagem de resultado */
			if(wallyIsInActualBlock)
			{
				for(i = 0; i < mask.nLines; i++)
					for(j = 0; j < mask.nCols; j++)
						resultImg.imgMatrix.mtx[relativeI+i][relativeJ+j] = pgmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
			}

			mtx_freeMatrixS16(blocoSendoAvaliado);
		}
	}

	return resultImg;
}

pgm_img_t pgm_findMaskInImagePercentage(pgm_img_t pgmImg, mtx_matrixS16_t mask,  uint8_t equalValorLimiar, float equalLimiarPercentage)
{
	pgm_img_t resultImg;
	mtx_matrixS16_t blocoSendoAvaliado;
	bool wallyIsInActualBlock = false;
	int i, j, relativeI, relativeJ, maxRelativeI, maxRelativeJ;

	resultImg = pgm_createEmptyImg(pgmImg.imgMatrix.nLines, pgmImg.imgMatrix.nCols);
	resultImg.maxValue = pgmImg.maxValue;

	maxRelativeI = pgmImg.imgMatrix.nLines-mask.nLines;
	maxRelativeJ = pgmImg.imgMatrix.nCols-mask.nCols;

	for(relativeI = 0; relativeI <= maxRelativeI; relativeI++){
		printf("\nRunning... %.2f%c", (((float)relativeI)/((float)maxRelativeI))*100.0,'%');
		for(relativeJ = 0; relativeJ <= maxRelativeJ; relativeJ++)
		{
			blocoSendoAvaliado = mtx_createMatrixS16(mask.nLines, mask.nCols);

			/* Copia um bloco da imagem original para matrixAux. */
			for(i = 0; i < blocoSendoAvaliado.nLines; i++)
				for(j = 0; j < blocoSendoAvaliado.nCols; j++)
					blocoSendoAvaliado.mtx[i][j] = pgmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];

			/* Verifica se o wally estah no bloco da imagem sendo analisada */
			wallyIsInActualBlock = mtx_equalsPercentage(blocoSendoAvaliado, mask, equalValorLimiar, equalLimiarPercentage);

			/* Caso um wally tenha sido encontrado na posicao avaliada,
			 * desenha o que encontrou na imagem de resultado */
			if(wallyIsInActualBlock)
			{
				for(i = 0; i < mask.nLines; i++)
					for(j = 0; j < mask.nCols; j++)
						resultImg.imgMatrix.mtx[relativeI+i][relativeJ+j] = pgmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
			}

			mtx_freeMatrixS16(blocoSendoAvaliado);
		}
	}

	return resultImg;
}

void pgm_printPgmImgStructure(pgm_img_t dataToPrint)
{
	int i,j;

	printf("\npgm_img_t:\n\tisOk: ");
	printf(dataToPrint.isOk ? "true" : "false");
	printf("\n\tNum colunas: %d\n\tNum linhas: %d\n\tMax value: %d", dataToPrint.imgMatrix.nCols, \
			dataToPrint.imgMatrix.nLines, dataToPrint.maxValue);

	printf("\n\tImg data:");
	mtx_printMatrixS16(dataToPrint.imgMatrix);
}

uint8_t* pgm_createHistogram(pgm_img_t imgToAnalyze)
{
	int i,j;
	uint8_t* histArray = malloc(PGM_PIXEL_MAX_VALUE);

	if(!imgToAnalyze.isOk)
	{
		printf("\npgm_createHistogram - ERRO imagem invalida.");
		return &histArray[0];
	}

	/* Preenche o array de resultados com 0s */
	for(i = 0; i <= imgToAnalyze.maxValue; i++)
		histArray[i] = 0;

	for(i = 0; i < imgToAnalyze.imgMatrix.nLines; i++)
		for(j = 0; j < imgToAnalyze.imgMatrix.nCols; j++)
			histArray[imgToAnalyze.imgMatrix.mtx[i][j]]++;

	return &histArray[0];
}

void pgm_saveHistogram(const char* fileName, uint8_t* histArray)
{
	FILE* fileToSave = fopen(fileName, "w");
	int i;

	if( fileToSave == NULL )
	{
		printf("\npgm_saveHistogram - Erro no salvamento da imagem: %s", fileToSave);
		return; /* Termina o programa. */
	}

	for(i = 0; i < PGM_PIXEL_MAX_VALUE; i++)
		fprintf(fileToSave, "%d\n", histArray[i]);

	printf("\npgm_saveHistogram  - Histograma salvo com sucesso no arquivo: %s", fileName);

	fclose(fileToSave);
}

bool pgm_equals(pgm_img_t img1, pgm_img_t img2)
{
	if(img1.isOk != img2.isOk || img1.maxValue != img2.maxValue || \
			img1.imgMatrix.nLines != img2.imgMatrix.nLines || img1.imgMatrix.nCols != img2.imgMatrix.nCols)
		return false;

	int i, j;

	for(i = 0; i < img1.imgMatrix.nLines; i++)
		for(j = 0; j < img2.imgMatrix.nCols; j++)
			if(img1.imgMatrix.mtx[i][j] != img2.imgMatrix.mtx[i][j])
				return false;

	return true;
}

//TODO - Verificar threshold
pgm_img_t pgm_applyMaskS16(pgm_img_t imgToApplyFilter, mtx_matrixS16_t maskToApply, uint8_t threshold)
{
	pgm_img_t resultantImg = pgm_createEmptyImg(imgToApplyFilter.imgMatrix.nLines, imgToApplyFilter.imgMatrix.nCols);
	mtx_pos_t* vizinhos;
	mtx_pos_t actualPos;
	int i, j, k, m, n, nVizinhos = 8, newPixelValue;

	for(i = 0; i < resultantImg.imgMatrix.nLines; i++)
		for(j = 0; j < resultantImg.imgMatrix.nCols; j++)
		{
			actualPos.lineIndex = i;
			actualPos.colIndex = j;
			vizinhos = mtx_getVizinhos8(actualPos, resultantImg.imgMatrix.nLines-1, resultantImg.imgMatrix.nCols-1);

			/* Primeiro calcula usando o centro da mascara. (pixel * w11) */
			newPixelValue = (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[1][1]);

			/* Agora calcula para o resto dos vizinhos 8 (pixel_vk * w_mn) */
			k = 0;
			for(m = 0; m < 3; m++)
				for(n = 0; n < 3; n++)
				{
					if( m == 1 && n == 1) /* Tem que considerar o proprio pixel e nao um vizinho. */
					{
						newPixelValue += (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[m][n]);
					}
					else /* Calcula a mascara usando os vizinhos */
					{
						/* Se tenho vizinho nessa posicao do pixel usa. */
						if(vizinhos[k].lineIndex >= 0 && vizinhos[k].colIndex >= 0)
						{
							newPixelValue += (imgToApplyFilter.imgMatrix.mtx[vizinhos[k].lineIndex][vizinhos[k].colIndex] * \
									maskToApply.mtx[m][n]);
						}

						/* Tendo ou nao vizinho vai para o proximo. */
						k++;
					}
				}

			newPixelValue /= nVizinhos;
			resultantImg.imgMatrix.mtx[i][j] = newPixelValue;

			free(vizinhos);
		}

	return resultantImg;
}

//TODO - Verificar threshold
pgm_img_t pgm_applyMaskFloat(pgm_img_t imgToApplyFilter, mtx_matrixFloat_t maskToApply, uint8_t threshold)
{
	pgm_img_t resultantImg = pgm_createEmptyImg(imgToApplyFilter.imgMatrix.nLines, imgToApplyFilter.imgMatrix.nCols);
	mtx_pos_t* vizinhos;
	mtx_pos_t actualPos;
	int i, j, k, m, n, nVizinhos = 8, newPixelValue;

	for(i = 0; i < resultantImg.imgMatrix.nLines; i++)
		for(j = 0; j < resultantImg.imgMatrix.nCols; j++)
		{
			actualPos.lineIndex = i;
			actualPos.colIndex = j;
			vizinhos = mtx_getVizinhos8(actualPos, resultantImg.imgMatrix.nLines-1, resultantImg.imgMatrix.nCols-1);

			/* Primeiro calcula usando o centro da mascara. (pixel * w11) */
			newPixelValue = (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[1][1]);

			/* Agora calcula para o resto dos vizinhos 8 (pixel_vk * w_mn) */
			k = 0;
			for(m = 0; m < 3; m++)
				for(n = 0; n < 3; n++)
				{
					if( m == 1 && n == 1) /* Tem que considerar o proprio pixel e nao um vizinho. */
					{
						newPixelValue += (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[m][n]);
					}
					else /* Calcula a mascara usando os vizinhos */
					{
						/* Se tenho vizinho nessa posicao do pixel usa. */
						if(vizinhos[k].lineIndex >= 0 && vizinhos[k].colIndex >= 0)
						{
							newPixelValue += (imgToApplyFilter.imgMatrix.mtx[vizinhos[k].lineIndex][vizinhos[k].colIndex] * \
									maskToApply.mtx[m][n]);
						}

						/* Tendo ou nao vizinho vai para o proximo. */
						k++;
					}
				}

			resultantImg.imgMatrix.mtx[i][j] = newPixelValue;

			free(vizinhos);
		}

	return resultantImg;
}

mtx_matrixFloat_t pgm_createCoocorrenciaMtx(pgm_img_t img, pgm_coocorrOrient_t orientacao, uint8_t d)
{
	mtx_matrixFloat_t coocorrenciaMtx;
	uint16_t min = 0xFFFF, max = 0;
	uint32_t freqSum = 0;
	int i, j, k, l;

	/* Encontra valores max e min */
	for(i = 0; i < img.imgMatrix.nLines; i++)
		for(j = 0; j < img.imgMatrix.nCols; j++)
		{
			if(img.imgMatrix.mtx[i][j] < min)
				min = img.imgMatrix.mtx[i][j];

			if(img.imgMatrix.mtx[i][j] > max)
				max = img.imgMatrix.mtx[i][j];
		}

	/* Aloca a matriz de coocorrencia. */
	coocorrenciaMtx = mtx_createMatrixFloat(max+1, max+1);

	switch(orientacao)
	{
	case _0_GRAUS:
		for(i = 0; i < img.imgMatrix.nLines; i++)
			for(j = 0; j < img.imgMatrix.nCols; j++)
			{
				/* Verifica os caras da direita. */
				l = 0;
				for(k = j+1; l < d && k < img.imgMatrix.nCols; k++ )
				{
					l++;
					coocorrenciaMtx.mtx[img.imgMatrix.mtx[i][k]][img.imgMatrix.mtx[i][j]]++;
				}

				/* Verifica os caras da esquerda. */
				l = 0;
				for(k = j-1; l < d && k > 0; k-- )
				{
					l++;
					coocorrenciaMtx.mtx[img.imgMatrix.mtx[i][k]][img.imgMatrix.mtx[i][j]]++;
				}
			}
		break;
	case _45_GRAUS:
		printf("\n45 graus");
		break;
	case _90_GRAUS:
		printf("\n90 graus");
		break;
	case _135_GRAUS:
		printf("\n135 graus");
		break;
	default:
		printf("\nDefault");
		break;
	}

	/* Soma todas as frequencias obtidas. */
	freqSum = 0;
	for(i = 0; i < coocorrenciaMtx.nLines; i++)
		for(j = 0; j < coocorrenciaMtx.nCols; j++)
			freqSum++;

	/* Calcula a porcentagem de aparicoes */
	for(i = 0; i < coocorrenciaMtx.nLines; i++)
		for(j = 0; j < coocorrenciaMtx.nCols; j++)
			coocorrenciaMtx.mtx[i][j] /= freqSum;

	mtx_printMatrixFloat(coocorrenciaMtx);
	printf("\nSoma: %d", freqSum);

	return coocorrenciaMtx;
}
