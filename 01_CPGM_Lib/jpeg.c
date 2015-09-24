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

pgm_img_t jpeg_applyDctToPgmImg(pgm_img_t originalPgmImg, uint8_t qualityMatrixToUse)
{
	int i = 0, j = 0, relativeBlockI = 0, relativeBlockJ = 0, maxRelativeI = 0, maxRelativeJ = 0;
	mtx_matrixFloat_t originalMatrix = mtx_convertS16ToFloatMatrix(originalPgmImg.imgMatrix);
	pgm_img_t resultImg = pgm_createEmptyImg(originalMatrix.nLines, originalMatrix.nCols);
	mtx_matrixFloat_t QMatrix;
	mtx_matrixFloat_t D;
	mtx_matrixFloat_t C;
	mtx_matrixFloat_t matrixAux8x8;

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

			/* Escreve o novo bloco apos a passagem do DCT na matriz da imagem de saída. */
			for(i = 0; i < 8; i++)
				for(j = 0; j < 8; j++)
				{
					resultImg.imgMatrix.mtx[relativeBlockI+i][relativeBlockJ+j] = (int16_t) C.mtx[i][j];
				}

			mtx_freeMatrixFloat(matrixAux8x8);
		}

	return resultImg;
}

