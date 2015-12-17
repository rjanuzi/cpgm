#include <ppm.h>

ppm_img_t ppm_createImg(const char* ppmFilePath)
{
	int fscanfResultAux, i, j, nLinesTemp, nColsTemp;
	long k;
	char stringAux[100];
	uint16_t intAux;
	ppm_img_t createdppmImg;
	FILE* ppmFile;
	bool ppmInASCII = false;
	bool temComentario = false;

	createdppmImg.isOk = false; /* Apenas se torna true se tudo estiver correto ao final. */

	/* Abrindo o arquivo */
	ppmFile = fopen(ppmFilePath, "r");

	if( ppmFile == NULL )
	{
		printf("\nERRO - ppm_createImg: Erro na abertura da imagem: %s", ppmFilePath);
		return createdppmImg; /* Termina o programa. */
	}

	/* Lendo o cabecalho */
	fscanfResultAux = fscanf(ppmFile, "%s", stringAux);
	/* A primeira coisa no deve ser a string "P2" (Magic Code) */
	if( fscanfResultAux == 0 )
	{
		printf("\nppm_createImg - ERRO: Header ppm invalido.");
		return createdppmImg;
	}
	else
	{
		if(strcmp(stringAux, ppm_MAGIC_CODE_ASCII) == 0)
			ppmInASCII = true;
		else
			if(strcmp(stringAux, ppm_MAGIC_CODE_BIN) == 0)
				ppmInASCII = false;
			else
			{
				printf("\nppm_createImg - ERRO: Magic CODE invalido: %s", stringAux);
				return createdppmImg;
			}

	}

	/* Pula texto TODO Melhorar esse Skip do comentario. */
	while( fscanf(ppmFile, "%s", stringAux) != EOF  )
	{
		if(strcmp(stringAux, "#") == 0)
			temComentario = true;

		/* O loop para (break) quando encotra uma string que pode ser convertida para um inteiro
		 * no caso de imagens ppm convertidas usando o GIMP eh a versao do filtro. */
		intAux = atoi(stringAux);
		if(intAux != 0)
			break;
	}
	if( fscanfResultAux == EOF )
	{
		printf("\nppm_createImg - ERRO: A estrutura do arquivo esta incorreta. 1");
		return createdppmImg;
	}

	if(!temComentario)
		nColsTemp = intAux; /* Se nao tiver comentario a string lida eh o numero de colunas. */
	else
	{
		/* Se tiver comentario, precisa ler o numero de colunas agora. */
		/* Recupera numero de cols */
		if((fscanfResultAux = fscanf(ppmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
			nColsTemp= intAux;
		else
		{
			printf("\nppm_createImg - ERRO: A estrutura do arquivo esta incorreta. 2");
			return createdppmImg;
		}
	}

	/* Recupera numero de linhas */
	if((fscanfResultAux = fscanf(ppmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		nLinesTemp = intAux;
	else
	{
		printf("\nppm_createImg - ERRO: A estrutura do arquivo esta incorreta. 3");
		return createdppmImg;
	}

	/* Recupera numero valor maximo */
	if((fscanfResultAux = fscanf(ppmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		createdppmImg.maxValue = intAux;
	else
	{
		printf("\nppm_createImg - ERRO: A estrutura do arquivo esta incorreta. 4");
		return createdppmImg;
	}

	if(ppmInASCII)
	{
		i = 0;
		j = 0;
		/* Recupera a matriz */
		createdppmImg.imgMatrix = mtx_createMatrixS16(nLinesTemp, nColsTemp);

		while( (fscanfResultAux = fscanf(ppmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		{
			createdppmImg.imgMatrix.mtx[i][j] = intAux;
			j++;
			if( j >= nColsTemp )
			{
				j = 0;
				i++;
			}
		}

		createdppmImg.isOk = true;
	}
	else
	{
		i = 0;
		j = 0;
		uint8_t auxData;
		long x;
		long size = nLinesTemp*nColsTemp;
		/* Recupera a matriz */
		createdppmImg.imgMatrix = mtx_createMatrixS16(nLinesTemp, nColsTemp);
		for(k = 0; k < size; k++)
		{
			if(fread((void*)&auxData, 1, 1, ppmFile) == 0)
			{
				printf("ERRO - ppm_createImg: fread leu 0 bytes.");
				break;
			}

			createdppmImg.imgMatrix.mtx[i][j] = auxData;
			j++;
			if( j >= nColsTemp )
			{
				j = 0;
				i++;
			}
		}

		createdppmImg.isOk = true;
	}

	fclose(ppmFile);

	return createdppmImg;
}

//ppm_img_t ppm_createEmptyImg(int nLines, int nCols)
//{
//	ppm_img_t newppmImage;
//
//	newppmImage.maxValue = ppm_PIXEL_MAX_VALUE;
//	newppmImage.imgMatrix = mtx_createMatrixS16(nLines, nCols);
//	if(newppmImage.imgMatrix.mtx != NULL)
//		newppmImage.isOk = true;
//	else
//		newppmImage.isOk = false;
//
//	return newppmImage;
//}
//
//void ppm_destroyppm(ppm_img_t ppmImgToDestroy)
//{
//	ppmImgToDestroy.isOk = false;
//	ppmImgToDestroy.maxValue = 0;
//	mtx_freeMatrixS16(ppmImgToDestroy.imgMatrix);
//}
//
//void ppm_saveppmImg(ppm_img_t ppmImgToSave, const char* fileName)
//{
//	FILE* fileToSave = fopen(fileName, "w");
//	int i,j;
//
//	if( fileToSave == NULL )
//	{
//		printf("\nERRO - ppm_saveppmImg: fileToSave == NULL", fileToSave);
//		return; /* Termina o programa. */
//	}
//
//	//	fprintf(fileToSave, ppm_MAGIC_CODE_BIN);
//	fprintf(fileToSave, ppm_MAGIC_CODE_ASCII);
//	fprintf(fileToSave, "\n");
//	fprintf(fileToSave, "# Arquivo criado com a biblioteca cppm Version 1.0\n");
//	fprintf(fileToSave, "%d %d\n", ppmImgToSave.imgMatrix.nCols, ppmImgToSave.imgMatrix.nLines);
//	fprintf(fileToSave, "%d\n", ppmImgToSave.maxValue);
//
//	for(i = 0; i < ppmImgToSave.imgMatrix.nLines; i++)
//		for(j = 0; j < ppmImgToSave.imgMatrix.nCols; j++)
//			//			fwrite((void*)&ppmImgToSave.imgMatrix.mtx[i][j], 1, 1, fileToSave);
//			fprintf(fileToSave, "%d\n", ppmImgToSave.imgMatrix.mtx[i][j]);
//
//	fclose(fileToSave);
//}
//
//void ppm_sumScalar(ppm_img_t ppmInputImg, int scalarToSum)
//{
//	mtx_sumScalarS16(ppmInputImg.imgMatrix, scalarToSum);
//}
//
//ppm_img_t ppm_diff(ppm_img_t ppmL, ppm_img_t ppmR)
//{
//	ppm_img_t resultImg;
//
//	resultImg.imgMatrix = mtx_subMatrixS16(ppmL.imgMatrix, ppmR.imgMatrix);
//	resultImg.maxValue = ppmL.maxValue;
//
//	if(resultImg.imgMatrix.mtx != NULL)
//		resultImg.isOk = true;
//	else
//		resultImg.isOk = false;
//
//	return resultImg;
//}
//
//ppm_img_t ppm_diffLim(ppm_img_t ppmL, ppm_img_t ppmR, int valorLimiar)
//{
//	ppm_img_t resultImg;
//	int i,j;
//
//	resultImg.imgMatrix = mtx_subMatrixS16(ppmL.imgMatrix, ppmR.imgMatrix);
//	resultImg.maxValue = ppmL.maxValue;
//
//	if(resultImg.imgMatrix.mtx != NULL)
//	{
//		resultImg.isOk = true;
//		for(i = 0; i < resultImg.imgMatrix.nLines; i++)
//			for(j = 0; j < resultImg.imgMatrix.nCols; j++)
//				if( resultImg.imgMatrix.mtx[i][j] > valorLimiar )
//					resultImg.imgMatrix.mtx[i][j] = 255;
//				else
//					resultImg.imgMatrix.mtx[i][j] = 0;
//	}
//	else
//		resultImg.isOk = false;
//
//	return resultImg;
//}
//
//ppm_img_t ppm_findMaskInImagePaP(ppm_img_t ppmImg, mtx_matrixS16_t mask, uint8_t limiarDeDiferenca)
//{
//	ppm_img_t resultImg;
//	mtx_matrixS16_t blocoSendoAvaliado;
//	bool wallyIsInActualBlock = false;
//	int i, j, relativeI, relativeJ, maxRelativeI, maxRelativeJ;
//
//	resultImg = ppm_createEmptyImg(ppmImg.imgMatrix.nLines, ppmImg.imgMatrix.nCols);
//	resultImg.maxValue = ppmImg.maxValue;
//
//	maxRelativeI = ppmImg.imgMatrix.nLines-mask.nLines;
//	maxRelativeJ = ppmImg.imgMatrix.nCols-mask.nCols;
//
//	for(relativeI = 0; relativeI <= maxRelativeI; relativeI++){
//		printf("\nRunning... %.2f%c", (((float)relativeI)/((float)maxRelativeI))*100.0,'%');
//		for(relativeJ = 0; relativeJ <= maxRelativeJ; relativeJ++)
//		{
//			blocoSendoAvaliado = mtx_createMatrixS16(mask.nLines, mask.nCols);
//
//			/* Copia um bloco da imagem original para matrixAux. */
//			for(i = 0; i < blocoSendoAvaliado.nLines; i++)
//				for(j = 0; j < blocoSendoAvaliado.nCols; j++)
//					blocoSendoAvaliado.mtx[i][j] = ppmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
//
//			/* Verifica se o wally estah no bloco da imagem sendo analisada */
//			wallyIsInActualBlock = mtx_equalsPaP(blocoSendoAvaliado, mask, limiarDeDiferenca);
//
//			/* Caso um wally tenha sido encontrado na posicao avaliada,
//			 * desenha o que encontrou na imagem de resultado */
//			if(wallyIsInActualBlock)
//			{
//				for(i = 0; i < mask.nLines; i++)
//					for(j = 0; j < mask.nCols; j++)
//						resultImg.imgMatrix.mtx[relativeI+i][relativeJ+j] = ppmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
//			}
//
//			mtx_freeMatrixS16(blocoSendoAvaliado);
//		}
//	}
//
//	return resultImg;
//}
//
//ppm_img_t ppm_findMaskInImageMean(ppm_img_t ppmImg, mtx_matrixS16_t mask, uint8_t limiarDeDiferenca)
//{
//	ppm_img_t resultImg;
//	mtx_matrixS16_t blocoSendoAvaliado;
//	bool wallyIsInActualBlock = false;
//	int i, j, relativeI, relativeJ, maxRelativeI, maxRelativeJ;
//
//	resultImg = ppm_createEmptyImg(ppmImg.imgMatrix.nLines, ppmImg.imgMatrix.nCols);
//	resultImg.maxValue = ppmImg.maxValue;
//
//	maxRelativeI = ppmImg.imgMatrix.nLines-mask.nLines;
//	maxRelativeJ = ppmImg.imgMatrix.nCols-mask.nCols;
//
//	for(relativeI = 0; relativeI <= maxRelativeI; relativeI++){
//		printf("\nRunning... %.2f%c", (((float)relativeI)/((float)maxRelativeI))*100.0,'%');
//		for(relativeJ = 0; relativeJ <= maxRelativeJ; relativeJ++)
//		{
//			blocoSendoAvaliado = mtx_createMatrixS16(mask.nLines, mask.nCols);
//
//			/* Copia um bloco da imagem original para matrixAux. */
//			for(i = 0; i < blocoSendoAvaliado.nLines; i++)
//				for(j = 0; j < blocoSendoAvaliado.nCols; j++)
//					blocoSendoAvaliado.mtx[i][j] = ppmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
//
//			/* Verifica se o wally estah no bloco da imagem sendo analisada */
//			wallyIsInActualBlock = mtx_equalsMean(blocoSendoAvaliado, mask, limiarDeDiferenca);
//
//			/* Caso um wally tenha sido encontrado na posicao avaliada,
//			 * desenha o que encontrou na imagem de resultado */
//			if(wallyIsInActualBlock)
//			{
//				for(i = 0; i < mask.nLines; i++)
//					for(j = 0; j < mask.nCols; j++)
//						resultImg.imgMatrix.mtx[relativeI+i][relativeJ+j] = ppmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
//			}
//
//			mtx_freeMatrixS16(blocoSendoAvaliado);
//		}
//	}
//
//	return resultImg;
//}
//
//ppm_img_t ppm_findMaskInImagePercentage(ppm_img_t ppmImg, mtx_matrixS16_t mask,  uint8_t equalValorLimiar, float equalLimiarPercentage)
//{
//	ppm_img_t resultImg;
//	mtx_matrixS16_t blocoSendoAvaliado;
//	bool wallyIsInActualBlock = false;
//	int i, j, relativeI, relativeJ, maxRelativeI, maxRelativeJ;
//
//	resultImg = ppm_createEmptyImg(ppmImg.imgMatrix.nLines, ppmImg.imgMatrix.nCols);
//	resultImg.maxValue = ppmImg.maxValue;
//
//	maxRelativeI = ppmImg.imgMatrix.nLines-mask.nLines;
//	maxRelativeJ = ppmImg.imgMatrix.nCols-mask.nCols;
//
//	for(relativeI = 0; relativeI <= maxRelativeI; relativeI++){
//		printf("\nRunning... %.2f%c", (((float)relativeI)/((float)maxRelativeI))*100.0,'%');
//		for(relativeJ = 0; relativeJ <= maxRelativeJ; relativeJ++)
//		{
//			blocoSendoAvaliado = mtx_createMatrixS16(mask.nLines, mask.nCols);
//
//			/* Copia um bloco da imagem original para matrixAux. */
//			for(i = 0; i < blocoSendoAvaliado.nLines; i++)
//				for(j = 0; j < blocoSendoAvaliado.nCols; j++)
//					blocoSendoAvaliado.mtx[i][j] = ppmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
//
//			/* Verifica se o wally estah no bloco da imagem sendo analisada */
//			wallyIsInActualBlock = mtx_equalsPercentage(blocoSendoAvaliado, mask, equalValorLimiar, equalLimiarPercentage);
//
//			/* Caso um wally tenha sido encontrado na posicao avaliada,
//			 * desenha o que encontrou na imagem de resultado */
//			if(wallyIsInActualBlock)
//			{
//				for(i = 0; i < mask.nLines; i++)
//					for(j = 0; j < mask.nCols; j++)
//						resultImg.imgMatrix.mtx[relativeI+i][relativeJ+j] = ppmImg.imgMatrix.mtx[relativeI+i][relativeJ+j];
//			}
//
//			mtx_freeMatrixS16(blocoSendoAvaliado);
//		}
//	}
//
//	return resultImg;
//}
//
//void ppm_printppmImgStructure(ppm_img_t dataToPrint)
//{
//	int i,j;
//
//	printf("\nppm_img_t:\n\tisOk: ");
//	printf(dataToPrint.isOk ? "true" : "false");
//	printf("\n\tNum colunas: %d\n\tNum linhas: %d\n\tMax value: %d", dataToPrint.imgMatrix.nCols, \
//			dataToPrint.imgMatrix.nLines, dataToPrint.maxValue);
//
//	printf("\n\tImg data:");
//	mtx_printMatrixS16(dataToPrint.imgMatrix);
//}
//
//uint8_t* ppm_createHistogram(ppm_img_t imgToAnalyze)
//{
//	int i,j;
//	uint8_t* histArray = malloc(ppm_PIXEL_MAX_VALUE);
//
//	if(!imgToAnalyze.isOk)
//	{
//		printf("\nppm_createHistogram - ERRO imagem invalida.");
//		return &histArray[0];
//	}
//
//	/* Preenche o array de resultados com 0s */
//	for(i = 0; i <= imgToAnalyze.maxValue; i++)
//		histArray[i] = 0;
//
//	for(i = 0; i < imgToAnalyze.imgMatrix.nLines; i++)
//		for(j = 0; j < imgToAnalyze.imgMatrix.nCols; j++)
//			histArray[imgToAnalyze.imgMatrix.mtx[i][j]]++;
//
//	return &histArray[0];
//}
//
//void ppm_saveHistogram(const char* fileName, uint8_t* histArray)
//{
//	FILE* fileToSave = fopen(fileName, "w");
//	int i;
//
//	if( fileToSave == NULL )
//	{
//		printf("\nppm_saveHistogram - Erro no salvamento da imagem: %s", fileToSave);
//		return; /* Termina o programa. */
//	}
//
//	for(i = 0; i < ppm_PIXEL_MAX_VALUE; i++)
//		fprintf(fileToSave, "%d\n", histArray[i]);
//
//	printf("\nppm_saveHistogram  - Histograma salvo com sucesso no arquivo: %s", fileName);
//
//	fclose(fileToSave);
//}
//
//bool ppm_equals(ppm_img_t img1, ppm_img_t img2)
//{
//	if(img1.isOk != img2.isOk || img1.maxValue != img2.maxValue || \
//			img1.imgMatrix.nLines != img2.imgMatrix.nLines || img1.imgMatrix.nCols != img2.imgMatrix.nCols)
//		return false;
//
//	int i, j;
//
//	for(i = 0; i < img1.imgMatrix.nLines; i++)
//		for(j = 0; j < img2.imgMatrix.nCols; j++)
//			if(img1.imgMatrix.mtx[i][j] != img2.imgMatrix.mtx[i][j])
//				return false;
//
//	return true;
//}
//
////TODO - Verificar threshold
//ppm_img_t ppm_applyMaskS16(ppm_img_t imgToApplyFilter, mtx_matrixS16_t maskToApply, uint8_t threshold)
//{
//	ppm_img_t resultantImg = ppm_createEmptyImg(imgToApplyFilter.imgMatrix.nLines, imgToApplyFilter.imgMatrix.nCols);
//	mtx_pos_t* vizinhos;
//	mtx_pos_t actualPos;
//	int i, j, k, m, n, nVizinhos = 8, newPixelValue;
//
//	for(i = 0; i < resultantImg.imgMatrix.nLines; i++)
//		for(j = 0; j < resultantImg.imgMatrix.nCols; j++)
//		{
//			actualPos.lineIndex = i;
//			actualPos.colIndex = j;
//			vizinhos = mtx_getVizinhos8(actualPos, resultantImg.imgMatrix.nLines-1, resultantImg.imgMatrix.nCols-1);
//
//			/* Primeiro calcula usando o centro da mascara. (pixel * w11) */
//			newPixelValue = (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[1][1]);
//
//			/* Agora calcula para o resto dos vizinhos 8 (pixel_vk * w_mn) */
//			k = 0;
//			for(m = 0; m < 3; m++)
//				for(n = 0; n < 3; n++)
//				{
//					if( m == 1 && n == 1) /* Tem que considerar o proprio pixel e nao um vizinho. */
//					{
//						newPixelValue += (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[m][n]);
//					}
//					else /* Calcula a mascara usando os vizinhos */
//					{
//						/* Se tenho vizinho nessa posicao do pixel usa. */
//						if(vizinhos[k].lineIndex >= 0 && vizinhos[k].colIndex >= 0)
//						{
//							newPixelValue += (imgToApplyFilter.imgMatrix.mtx[vizinhos[k].lineIndex][vizinhos[k].colIndex] * \
//									maskToApply.mtx[m][n]);
//						}
//
//						/* Tendo ou nao vizinho vai para o proximo. */
//						k++;
//					}
//				}
//
//			newPixelValue /= nVizinhos;
//			resultantImg.imgMatrix.mtx[i][j] = newPixelValue;
//
//			free(vizinhos);
//		}
//
//	return resultantImg;
//}
//
////TODO - Verificar threshold
//ppm_img_t ppm_applyMaskFloat(ppm_img_t imgToApplyFilter, mtx_matrixFloat_t maskToApply, uint8_t threshold)
//{
//	ppm_img_t resultantImg = ppm_createEmptyImg(imgToApplyFilter.imgMatrix.nLines, imgToApplyFilter.imgMatrix.nCols);
//	mtx_pos_t* vizinhos;
//	mtx_pos_t actualPos;
//	int i, j, k, m, n, nVizinhos = 8, newPixelValue;
//
//	for(i = 0; i < resultantImg.imgMatrix.nLines; i++)
//		for(j = 0; j < resultantImg.imgMatrix.nCols; j++)
//		{
//			actualPos.lineIndex = i;
//			actualPos.colIndex = j;
//			vizinhos = mtx_getVizinhos8(actualPos, resultantImg.imgMatrix.nLines-1, resultantImg.imgMatrix.nCols-1);
//
//			/* Primeiro calcula usando o centro da mascara. (pixel * w11) */
//			newPixelValue = (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[1][1]);
//
//			/* Agora calcula para o resto dos vizinhos 8 (pixel_vk * w_mn) */
//			k = 0;
//			for(m = 0; m < 3; m++)
//				for(n = 0; n < 3; n++)
//				{
//					if( m == 1 && n == 1) /* Tem que considerar o proprio pixel e nao um vizinho. */
//					{
//						newPixelValue += (imgToApplyFilter.imgMatrix.mtx[i][j] * maskToApply.mtx[m][n]);
//					}
//					else /* Calcula a mascara usando os vizinhos */
//					{
//						/* Se tenho vizinho nessa posicao do pixel usa. */
//						if(vizinhos[k].lineIndex >= 0 && vizinhos[k].colIndex >= 0)
//						{
//							newPixelValue += (imgToApplyFilter.imgMatrix.mtx[vizinhos[k].lineIndex][vizinhos[k].colIndex] * \
//									maskToApply.mtx[m][n]);
//						}
//
//						/* Tendo ou nao vizinho vai para o proximo. */
//						k++;
//					}
//				}
//
//			resultantImg.imgMatrix.mtx[i][j] = newPixelValue;
//
//			free(vizinhos);
//		}
//
//	return resultantImg;
//}
//
//mtx_matrixFloat_t ppm_createCoocorrenciaMtx(ppm_img_t img, ppm_coocorrOrient_t orientacao, uint8_t d)
//{
//	mtx_matrixFloat_t coocorrenciaMtx;
//	uint16_t min = 0xFFFF, max = 0;
//	uint32_t freqSum = 0;
//	int i, j, k, l;
//
//	/* Encontra valores max e min */
//	for(i = 0; i < img.imgMatrix.nLines; i++)
//		for(j = 0; j < img.imgMatrix.nCols; j++)
//		{
//			if(img.imgMatrix.mtx[i][j] < min)
//				min = img.imgMatrix.mtx[i][j];
//
//			if(img.imgMatrix.mtx[i][j] > max)
//				max = img.imgMatrix.mtx[i][j];
//		}
//
//	/* Aloca a matriz de coocorrencia. */
//	coocorrenciaMtx = mtx_createMatrixFloat(max+1, max+1);
//
//	switch(orientacao)
//	{
//	case _0_GRAUS:
//		for(i = 0; i < img.imgMatrix.nLines; i++)
//			for(j = 0; j < img.imgMatrix.nCols; j++)
//			{
//				/* Verifica os caras da direita. */
//				l = 0;
//				for(k = j+1; l < d && k < img.imgMatrix.nCols; k++ )
//				{
//					l++;
//					coocorrenciaMtx.mtx[img.imgMatrix.mtx[i][k]][img.imgMatrix.mtx[i][j]]++;
//				}
//
//				/* Verifica os caras da esquerda. */
//				l = 0;
//				for(k = j-1; l < d && k > 0; k-- )
//				{
//					l++;
//					coocorrenciaMtx.mtx[img.imgMatrix.mtx[i][k]][img.imgMatrix.mtx[i][j]]++;
//				}
//			}
//		break;
//	case _45_GRAUS:
//		printf("\n45 graus");
//		break;
//	case _90_GRAUS:
//		printf("\n90 graus");
//		break;
//	case _135_GRAUS:
//		printf("\n135 graus");
//		break;
//	default:
//		printf("\nDefault");
//		break;
//	}
//
//	/* Soma todas as frequencias obtidas. */
//	freqSum = 0;
//	for(i = 0; i < coocorrenciaMtx.nLines; i++)
//		for(j = 0; j < coocorrenciaMtx.nCols; j++)
//			freqSum++;
//
//	/* Calcula a porcentagem de aparicoes */
//	for(i = 0; i < coocorrenciaMtx.nLines; i++)
//		for(j = 0; j < coocorrenciaMtx.nCols; j++)
//			coocorrenciaMtx.mtx[i][j] /= freqSum;
//
//	mtx_printMatrixFloat(coocorrenciaMtx);
//	printf("\nSoma: %d", freqSum);
//
//	return coocorrenciaMtx;
//}
