#include <jpeg.h>

const float jpeg_dctMatrixT[8][8] = \
{
	{ .3536, .3536,  .3536,  .3536,  .3536,  .3536,  .3536,  .3536 }, \
	{ .4904, .4157,  .2778,  .0975,  -.0975, -.2778, -.4157, -.4904}, \
	{ .4619, .1913,  -.1913, -.4619, -.4619, -.1913, .1913,  .4619},  \
	{ .4157, -.0975, -.4904, -.2778, .2778,  .4904,  .0975,  -.4157}, \
	{ .3536, -.3536, -.3536, .3536,  .3536,  -.3536, -.3536,  .3536},  \
	{ .2778, -.4904, .0975,  .4157, -.4157,  -.0975, .4904,  -.2778}, \
	{ .1913, -.4619, .4619, -.1913, -.1913,  .4619,  -.4619, .1913 }, \
	{ .0975, -.2778, .4157, -.4904, .4904,   -.4157, .2778,  -.0975}, \
};

const float jpeg_testMatrixOriginal[8][8] = \
		{
	{ 154, 123, 123, 123, 123, 123, 123, 136}, \
	{ 192, 180, 136, 154, 154, 154, 136, 110}, \
	{ 254, 198, 154, 154, 180, 154, 123, 123}, \
	{ 239, 180, 136, 180, 180, 166, 123, 123}, \
	{ 180, 154, 136, 167, 166, 149, 136, 136}, \
	{ 128, 136, 123, 136, 154, 180, 198, 154}, \
	{ 123, 105, 110, 149, 136, 136, 180, 166}, \
	{ 110, 136, 123, 123, 123, 136, 154, 136}, \
		};

const float jpeg_Q10[8][8] = \
		{
	{80,  60,  50,  80,  120, 200, 255, 255}, \
	{55,  60,  70,  95,  130, 255, 255, 255}, \
	{70,  65,  80,  120, 200, 255, 255, 255}, \
	{70,  85,  110, 145, 255, 255, 255, 255}, \
	{90,  110, 185, 255, 255, 255, 255, 255}, \
	{120, 175, 255, 255, 255, 255, 255, 255}, \
	{245, 255, 255, 255, 255, 255, 255, 255}, \
	{255, 255, 255, 255, 255, 255, 255, 255}, \
		};

const float jpeg_Q50[8][8] = \
		{
	{ 16, 11, 10, 16, 24, 40,   51,  61},  \
	{ 12, 12, 14, 19, 26, 58,   60,  55},  \
	{ 14, 13, 16, 24, 40, 57,   69,  56},  \
	{ 14, 17, 22, 29, 51, 87,   80,  62},  \
	{ 18, 22, 37, 56, 68, 109,  103, 77},  \
	{ 24, 35, 55, 64, 81, 104,  113, 92},  \
	{ 49, 64, 78, 87, 103, 121, 120, 101}, \
	{ 72, 92, 95, 98, 112, 100, 103, 99},  \
		};

const float jpeg_Q90[8][8] = \
		{
	{3,  2, 2,  3,  5,  8,  10, 12},  \
	{2,  2, 3,  4,  5,  12, 12, 11},  \
	{3,  3, 3,  5,  8,  11, 14, 11},  \
	{3,  3, 4,  6,  10, 17, 16, 12},  \
	{4,  4, 7,  11, 14, 22, 21, 15},  \
	{5,  7, 11, 13, 16, 12, 23, 18},  \
	{10, 13, 16, 17, 21, 24, 24, 21}, \
	{14, 18, 19, 20, 22, 20, 20, 20}, \
		};

mtx_matrixFloat_t jpeg_createDctMatrixT8x8()
{
	int i,j;
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);

	for(i = 0; i < JPEG_DCT_BLOCK_SIZE; i++)
		for(j = 0; j < JPEG_DCT_BLOCK_SIZE; j++)
			resultMatrix.mtx[i][j] = jpeg_dctMatrixT[i][j];

	return resultMatrix;
}

mtx_matrixFloat_t jpeg_createTestMatrixOriginal8x8()
{
	int i,j;
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);

	for(i = 0; i < JPEG_DCT_BLOCK_SIZE; i++)
		for(j = 0; j < JPEG_DCT_BLOCK_SIZE; j++)
			resultMatrix.mtx[i][j] = jpeg_testMatrixOriginal[i][j];

	return resultMatrix;
}

mtx_matrixFloat_t jpeg_createDctMatrixQ108x8()
{
	int i,j;
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);

	for(i = 0; i < JPEG_DCT_BLOCK_SIZE; i++)
		for(j = 0; j < JPEG_DCT_BLOCK_SIZE; j++)
			resultMatrix.mtx[i][j] = jpeg_Q10[i][j];

	return resultMatrix;
}

mtx_matrixFloat_t jpeg_createDctMatrixQ508x8()
{
	int i,j;
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);

	for(i = 0; i < JPEG_DCT_BLOCK_SIZE; i++)
		for(j = 0; j < JPEG_DCT_BLOCK_SIZE; j++)
			resultMatrix.mtx[i][j] = jpeg_Q50[i][j];

	return resultMatrix;
}

mtx_matrixFloat_t jpeg_createDctMatrixQ908x8()
{
	int i,j;
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);

	for(i = 0; i < JPEG_DCT_BLOCK_SIZE; i++)
		for(j = 0; j < JPEG_DCT_BLOCK_SIZE; j++)
			resultMatrix.mtx[i][j] = jpeg_Q90[i][j];

	return resultMatrix;
}

mtx_matrixFloat_t jpeg_calcMatrixD8x8(mtx_matrixFloat_t originalMatrix)
{
	mtx_matrixFloat_t T = jpeg_createDctMatrixT8x8();
	mtx_matrixFloat_t T_transposta = mtx_transposeMtxFloat(T);
	mtx_matrixFloat_t D;
	mtx_matrixFloat_t matrixAux;
	mtx_sumScalarFloat(originalMatrix, -128);

	/* Calculando T*M */
	D = mtx_prodMatrixFloat(T, originalMatrix);
	matrixAux = D;
	/* Calculando (T*M)*T' */
	D = mtx_prodMatrixFloat(D, T_transposta);
	mtx_freeMatrixFloat(matrixAux);

	return D;
}

pgm_img_t jpeg_applyDctToPgmImg(pgm_img_t originalPgmImg, uint8_t qualityMatrixToUse, const char* outputFile)
{
	int i = 0, j = 0, relativeBlockI = 0, relativeBlockJ = 0, maxRelativeI = 0, maxRelativeJ = 0, blockCount = 0;
	float totalCompression = 0.0;
	mtx_matrixFloat_t originalMatrix = mtx_convertS16ToFloatMatrix(originalPgmImg.imgMatrix);
	pgm_img_t resultImg = pgm_createEmptyImg(originalMatrix.nLines, originalMatrix.nCols);
	mtx_matrixFloat_t QMatrix;
	mtx_matrixFloat_t D;
	mtx_matrixS16_t C;
	mtx_matrixFloat_t matrixAux8x8;
	mtx_arrayS16_t compressedDataAux;
	FILE* fileToSave = fopen(outputFile, "w");

	if(fileToSave == NULL)
	{
		printf("\nERRO: jpeg_applyDctToPgmImg - Nao foi possivel abrir o arquivo fileToSave no caminho %s!", outputFile);
		return resultImg;
	}

	fprintf( fileToSave, "#Pseudo-Compressed PGM Img\n%d %d", originalPgmImg.imgMatrix.nLines, originalPgmImg.imgMatrix.nCols );

	switch(qualityMatrixToUse)
	{
	case JPEG_QUALITY_MATRIX_TO_USE_Q10:
		QMatrix = jpeg_createDctMatrixQ108x8();
		break;

	case JPEG_QUALITY_MATRIX_TO_USE_Q50:
		QMatrix = jpeg_createDctMatrixQ508x8();
		break;

	case JPEG_QUALITY_MATRIX_TO_USE_Q90:
		QMatrix = jpeg_createDctMatrixQ908x8();
		break;

	default:
		QMatrix = jpeg_createDctMatrixQ908x8();
		break;
	}

	if( originalPgmImg.imgMatrix.nLines % 8 != 0 || originalPgmImg.imgMatrix.nCols % 8 != 0 )
	{
		printf("\nERRO: jpeg_applyDctToPgmImg - O numero de linhas E o numero de colunas da imagem devem ser multiplos de 8!");
		return resultImg;
	}

	maxRelativeI = originalPgmImg.imgMatrix.nLines;
	maxRelativeJ = originalPgmImg.imgMatrix.nCols;
	for(relativeBlockI = 0; relativeBlockI < maxRelativeI; relativeBlockI += 8)
		for(relativeBlockJ = 0; relativeBlockJ < maxRelativeJ; relativeBlockJ += 8)
		{
			blockCount++;
			matrixAux8x8 = mtx_createMatrixFloat(8,8);

			/* Preenche a matriz auxiliar com o bloco 8x8 da matriz da imagem original
			 * onde serah aplicado o algoritmo DCT. */
			for(i = 0; i < 8; i++)
				for(j = 0; j < 8; j++)
				{
					matrixAux8x8.mtx[i][j] = originalMatrix.mtx[relativeBlockI+i][relativeBlockJ+j];
				}

			D = jpeg_calcMatrixD8x8(matrixAux8x8);
			C = mtx_divMatrixElemFloat(D,QMatrix);

			/* Cria e salva array de compressao com os dados. */
			compressedDataAux = mtx_zigZagCompressMatrix(C);

			/* Vai somando as taxas de compressao para tirar uma media no final. */
			totalCompression += ((((float)compressedDataAux.size)/(64.0))*100.0);
			fprintf(fileToSave, "\n%d ", compressedDataAux.size);
			for(i = 0; i < compressedDataAux.size; i++)
				fprintf(fileToSave, "%d ", compressedDataAux.array[i]);

			/* Escreve o novo bloco apos a passagem do DCT na matriz da imagem de saída. */
			for(i = 0; i < 8; i++)
				for(j = 0; j < 8; j++)
				{
					resultImg.imgMatrix.mtx[relativeBlockI+i][relativeBlockJ+j] = C.mtx[i][j];
				}

			mtx_freeMatrixFloat(matrixAux8x8);
		}

	printf("\njpeg_applyDctToPgmImg - Compressao media dos blocos obtida: %.2f%c", 100.0-totalCompression/((float)blockCount), '%' );

	fclose(fileToSave);

	return resultImg;
}

pgm_img_t jpeg_recoveryPciImg(const char* inputPciFileName)
{
	FILE* inputFile = fopen(inputPciFileName, "r");
	int fscanfResultAux, intAux, nLinesAux, nColsAux, i = 0, j = 0, k = 0, relativeBlockI = 0, relativeBlockJ = 0, sizeAux;
	char stringAux[100];
	pgm_img_t resultImg;
	mtx_matrixS16_t matrix8x8Aux;
	mtx_arrayS16_t arrayAux = mtx_createArrayS16(JPEG_DCT_BLOCK_SIZE*JPEG_DCT_BLOCK_SIZE);

	if( inputFile == NULL )
	{
		printf("\njpeg_recoveryPciImg - Erro na abertura do arquivo: %s", inputFile);
		return resultImg; /* Termina o programa. */
	}

	/* Lendo o cabecalho */
	fgets(stringAux, JPEG_PCI_HEADER_SIZE, inputFile);
	/* A primeira coisa no deve ser a string #Pseudo-Compressed PGM Img */
	if( fscanfResultAux == 0 || (strcmp(stringAux, "#Pseudo-Compressed PGM Img") != 0 ) )
	{
		printf("\njpeg_recoveryPciImg - ERRO: Header PCI invalido. Founded: %s", stringAux);
		return resultImg;
	}

	/* Recupera numero de linhas */
	if((fscanfResultAux = fscanf(inputFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		nLinesAux = intAux;
	else
	{
		printf("\njpeg_recoveryPciImg - ERRO: A estrutura do arquivo esta incorreta.");
		return resultImg;
	}

	/* Recupera numero de colunas */
	if((fscanfResultAux = fscanf(inputFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		nColsAux = intAux;
	else
	{
		printf("\njpeg_recoveryPciImg - ERRO: A estrutura do arquivo esta incorreta.");
		return resultImg;
	}

	if( nLinesAux % 8 != 0 || nColsAux % 8 != 0 )
	{
		printf("\nERRO: njpeg_recoveryPciImg - o arquivo PCI deve ter informacao suficiente para montar uma imagem proporcional a 8x8!");
		return resultImg;
	}

	/* Cria a matriz de resultado. */
	resultImg.imgMatrix = mtx_createMatrixS16(nLinesAux, nColsAux);
	resultImg.isOk = false; /* Serah correto apenas se conseguir finalizar a funcao. */

	int x = 2;
	while( (fscanfResultAux = fscanf(inputFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
	{
		arrayAux = mtx_createArrayS16(intAux);
		k = 0;

		/* A verificacao do k tem que ser a primeira avaliacao para n ler um inteiro a mais. */
		while( k < arrayAux.size && (fscanfResultAux = fscanf(inputFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
			arrayAux.array[k++] = intAux;

		matrix8x8Aux = mtx_zigZagDecompressMatrix(arrayAux, JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);
		mtx_freeArrayS16(arrayAux);

		/* Escreve na matriz da imagem resultante apos recuperar os dados do array de compressao. */
		for(i = 0; i < matrix8x8Aux.nLines; i++)
			for(j = 0; j < matrix8x8Aux.nCols; j++)
			{
				resultImg.imgMatrix.mtx[relativeBlockI+i][relativeBlockJ+j] = matrix8x8Aux.mtx[i][j];
			}
		relativeBlockJ += 8;
		if( relativeBlockJ >= nColsAux )
		{
			relativeBlockJ = 0;
			relativeBlockI += 8;
		}
	}

	resultImg.isOk = true;

	fclose(inputFile);

	return resultImg;
}
