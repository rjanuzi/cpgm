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

mtx_matrixFloat_t jpeg_createDctMatrixT()
{
	int i,j;
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);

	for(i = 0; i < JPEG_DCT_BLOCK_SIZE; i++)
		for(j = 0; j < JPEG_DCT_BLOCK_SIZE; j++)
			resultMatrix.mtx[i][j] = jpeg_dctMatrixT[i][j];

	return resultMatrix;
}

mtx_matrixFloat_t jpeg_createTestMatrixOriginal()
{
	int i,j;
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(JPEG_DCT_BLOCK_SIZE, JPEG_DCT_BLOCK_SIZE);

	for(i = 0; i < JPEG_DCT_BLOCK_SIZE; i++)
		for(j = 0; j < JPEG_DCT_BLOCK_SIZE; j++)
			resultMatrix.mtx[i][j] = jpeg_testMatrixOriginal[i][j];

	return resultMatrix;
}

mtx_matrixFloat_t jpeg_calcMatrixD(mtx_matrixFloat_t originalMatrix)
{
	mtx_matrixFloat_t T = jpeg_createDctMatrixT();
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

