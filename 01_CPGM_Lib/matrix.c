#include <matrix.h>

mtx_matrixS16_t mtx_createMatrixU8(int nLines, int nCols)
{
	int i,j;
	mtx_matrixS16_t newMatrix;

	newMatrix.nLines = nLines;
	newMatrix.nCols = nCols;

	newMatrix.mtx = malloc(nLines*sizeof(uint8_t*));

	if(newMatrix.mtx != NULL)
		for(i = 0; i < nLines; i++)
		{
			newMatrix.mtx[i] = malloc(nCols*sizeof(uint8_t*));
			for( j = 0; j < nCols; j++)
				newMatrix.mtx[i][j] = 0;
		}

	return newMatrix;
}

mtx_matrixFloat_t mtx_createMatrixFloat(int nLines, int nCols)
{
	int i,j;
	mtx_matrixFloat_t newMatrix;

	newMatrix.nLines = nLines;
	newMatrix.nCols = nCols;

	newMatrix.mtx = malloc(nLines*sizeof(float*));

	if(newMatrix.mtx != NULL)
		for(i = 0; i < nLines; i++)
		{
			newMatrix.mtx[i] = malloc(nCols*sizeof(float*));
			for( j = 0; j < nCols; j++)
				newMatrix.mtx[i][j] = 0.0;
		}

	return newMatrix;
}

void mtx_freeMatrixU8(mtx_matrixS16_t matrixToFree)
{
	int i;

	for(i = 0; i < matrixToFree.nLines; i++)
		free(matrixToFree.mtx[i]);
	free(matrixToFree.mtx);
}

void mtx_freeMatrixFloat(mtx_matrixFloat_t matrixToFree)
{
	int i;

	for(i = 0; i < matrixToFree.nLines; i++)
		free(matrixToFree.mtx[i]);
	free(matrixToFree.mtx);
}

void mtx_sumScalarU8(mtx_matrixS16_t matrixToUpdate, int scalar)
{
	int i,j, aux;

	for(i = 0; i < matrixToUpdate.nLines; i++)
		for(j = 0; j < matrixToUpdate.nCols; j++)
		{
			aux = matrixToUpdate.mtx[i][j] + scalar;

			if(aux < 0)
				matrixToUpdate.mtx[i][j] = 0;
			else
				if(aux > 255)
					matrixToUpdate.mtx[i][j] = 255;
				else
					matrixToUpdate.mtx[i][j] = aux;
		}
}

void mtx_sumScalarFloat(mtx_matrixFloat_t matrixToUpdate, float scalar)
{
	int i,j;

	for(i = 0; i < matrixToUpdate.nLines; i++)
		for(j = 0; j < matrixToUpdate.nCols; j++)
			matrixToUpdate.mtx[i][j] += scalar;
}

void mtx_multScalarFloat(mtx_matrixFloat_t matrixUpdate, float scalar)
{
	int i,j;

	for(i = 0; i < matrixUpdate.nLines; i++)
		for(j = 0; j < matrixUpdate.nCols; j++)
			matrixUpdate.mtx[i][j] *= scalar;
}

mtx_matrixFloat_t mtx_transposeMtxFloat(mtx_matrixFloat_t matrixToTranspose)
{
	int i, j;
	mtx_matrixFloat_t transposedMatrix = mtx_createMatrixFloat(matrixToTranspose.nCols, matrixToTranspose.nLines);

	for( i = 0; i < transposedMatrix.nLines; i++)
		for( j = 0; j < transposedMatrix.nCols; j++)
			transposedMatrix.mtx[i][j] = matrixToTranspose.mtx[j][i];

	return transposedMatrix;
}

mtx_matrixFloat_t mtx_prodMatrixFloat(mtx_matrixFloat_t matrixL, mtx_matrixFloat_t matrixR)
{
	int i, j, k;
	mtx_matrixFloat_t resultMatrix;

	if(matrixL.nCols != matrixR.nLines)
	{
		printf("\nERRO: mtx_multMatrixFloat - O numero de colunas da primeira deve ser igual ao numero de linhas da segunda!");
		return resultMatrix;
	}

	resultMatrix = mtx_createMatrixFloat(matrixL.nLines, matrixR.nCols);

	for(i = 0; i < resultMatrix.nLines; i++)
		for(j = 0; j < resultMatrix.nCols; j++)
			for(k = 0; k < matrixL.nCols; k++)
				resultMatrix.mtx[i][j] += (matrixL.mtx[i][k] * matrixR.mtx[k][j]); /* resultMatrix[i][j] começa com zeros */

	return resultMatrix;
}

mtx_matrixFloat_t mtx_divMatrixElemFloat(mtx_matrixFloat_t matrixL, mtx_matrixFloat_t matrixR)
{
	int i, j;
	mtx_matrixFloat_t resultMatrix;

	if(matrixL.nLines != matrixR.nLines || matrixL.nCols != matrixR.nCols)
	{
		printf("\nERRO: mtx_divMatrixElemFloat - O numero linhas e colunas devem ser iguais entre as duas matrizes.");
		return resultMatrix;
	}

	for(i = 0; i < resultMatrix.nLines; i++)
		for(j = 0; j < resultMatrix.nCols; j++)
			resultMatrix.mtx[i][j] = roundf(matrixL.mtx[i][j] / matrixR.mtx[i][j]);

	return resultMatrix;
}

mtx_matrixS16_t mtx_subMatrixU8(mtx_matrixS16_t matrixL, mtx_matrixS16_t matrixR)
{
	int i, j, iMax, jMax;
	mtx_matrixS16_t resultMatrix;

	if( matrixL.nLines < matrixR.nLines )
		iMax = matrixL.nLines;
	else
		iMax = matrixR.nLines;

	if( matrixL.nCols < matrixR.nCols )
		jMax = matrixL.nCols;
	else
		jMax = matrixR.nCols;

	resultMatrix = mtx_createMatrixU8(iMax, jMax);

	if(resultMatrix.mtx != NULL)
		for(i = 0; i < iMax; i++)
			for(j = 0; j < jMax; j++)
				resultMatrix.mtx[i][j] = abs(matrixL.mtx[i][j] - matrixR.mtx[i][j]);

	return resultMatrix;
}

mtx_matrixFloat_t mtx_convertU8ToFloatMatrix(mtx_matrixS16_t originalMatrix)
{
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(originalMatrix.nLines, originalMatrix.nCols);
	int i,j;

	for(i = 0; i < originalMatrix.nLines; i++)
		for(j = 0; j < originalMatrix.nCols; j++)
			resultMatrix.mtx[i][j] = (float) originalMatrix.mtx[i][j];

	return resultMatrix;
}

void mtx_printMatrixU8(mtx_matrixS16_t matrixToPrint)
{
	int i,j;

	printf("\nMatrix[%d][%d]: ", matrixToPrint.nLines, matrixToPrint.nCols);
	for(i = 0; i < matrixToPrint.nLines; i++)
	{
		printf("\n");
		for(j = 0; j < matrixToPrint.nCols; j++)
			printf(" %d ", matrixToPrint.mtx[i][j]);
	}
}

void mtx_printMatrixFloat(mtx_matrixFloat_t matrixToPrint)
{
	int i,j;

	printf("\nMatrix[%d][%d]: ", matrixToPrint.nLines, matrixToPrint.nCols);
	for(i = 0; i < matrixToPrint.nLines; i++)
	{
		printf("\n");
		for(j = 0; j < matrixToPrint.nCols; j++)
			printf(" %.4f ", matrixToPrint.mtx[i][j]);
	}
}
