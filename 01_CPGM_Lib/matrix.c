#include <matrix.h>

mtx_matrix8_t mtx_createMatrix8(int nLines, int nCols)
{
	int i,j;
	mtx_matrix8_t newMatrix;

	newMatrix.nLines = nLines;
	newMatrix.nCols = nCols;

	newMatrix.mtx = malloc(nLines*sizeof(uint8_t*));

	if(newMatrix.mtx != NULL)
		for(i = 0; i < nLines; i++)
		{
			newMatrix.mtx[i] = malloc(nCols);
			for( j = 0; j < nCols; j++)
				newMatrix.mtx[i][j] = 0;
		}

	return newMatrix;
}

void mtx_freeMatrix8(mtx_matrix8_t matrixToFree)
{
	int i;

	for(i = 0; i < matrixToFree.nLines; i++)
		free(matrixToFree.mtx[i]);
	free(matrixToFree.mtx);
}

void mtx_sumScalar8(mtx_matrix8_t matrixUpdate, int scalar)
{
	int i,j, aux;

	for(i = 0; i < matrixUpdate.nLines; i++)
		for(j = 0; j < matrixUpdate.nCols; j++)
		{
			aux = matrixUpdate.mtx[i][j] + scalar;

			if(aux < 0)
				matrixUpdate.mtx[i][j] = 0;
			else
				if(aux > 255)
					matrixUpdate.mtx[i][j] = 255;
				else
					matrixUpdate.mtx[i][j] = aux;
		}
}

mtx_matrix8_t mtx_subMatrix8(mtx_matrix8_t matrixL, mtx_matrix8_t matrixR)
{
	int i, j, iMax, jMax;
	mtx_matrix8_t resultMatrix;

	if( matrixL.nLines < matrixR.nLines )
		iMax = matrixL.nLines;
	else
		iMax = matrixR.nLines;

	if( matrixL.nCols < matrixR.nCols )
		jMax = matrixL.nCols;
	else
		jMax = matrixR.nCols;

	resultMatrix = mtx_createMatrix8(iMax, jMax);

	if(resultMatrix.mtx != NULL)
		for(i = 0; i < iMax; i++)
			for(j = 0; j < jMax; j++)
				resultMatrix.mtx[i][j] = abs(matrixL.mtx[i][j] - matrixR.mtx[i][j]);

	return resultMatrix;
}

void mtx_printMatrix8(mtx_matrix8_t matrixToPrint)
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
