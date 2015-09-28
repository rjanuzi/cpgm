#include <matrix.h>

mtx_matrixS16_t mtx_createMatrixS16(int nLines, int nCols)
{
	int i,j;
	mtx_matrixS16_t newMatrix;

	newMatrix.nLines = nLines;
	newMatrix.nCols = nCols;

	newMatrix.mtx = malloc(nLines*sizeof(int16_t*));

	if(newMatrix.mtx != NULL)
		for(i = 0; i < nLines; i++)
		{
			newMatrix.mtx[i] = malloc(nCols*sizeof(int16_t*));
			for( j = 0; j < nCols; j++)
				newMatrix.mtx[i][j] = 0;
		}

	return newMatrix;
}

mtx_arrayS16_t mtx_createArrayS16(int size)
{
	int i;
	mtx_arrayS16_t newArray;

	newArray.size = size;

	newArray.array = malloc(size*sizeof(int16_t*));

	if(newArray.array != NULL)
		for(i = 0; i < size; i++)
		{
			newArray.array[i] = 0;
		}

	return newArray;
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

void mtx_freeMatrixS16(mtx_matrixS16_t matrixToFree)
{
	int i;

	for(i = 0; i < matrixToFree.nLines; i++)
		free(matrixToFree.mtx[i]);
	free(matrixToFree.mtx);
}

void mtx_freeArrayS16(mtx_arrayS16_t arrayToFree)
{
	free(arrayToFree.array);
}

void mtx_freeMatrixFloat(mtx_matrixFloat_t matrixToFree)
{
	int i;

	for(i = 0; i < matrixToFree.nLines; i++)
		free(matrixToFree.mtx[i]);
	free(matrixToFree.mtx);
}

void mtx_sumScalarS16(mtx_matrixS16_t matrixToUpdate, int scalar)
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

mtx_matrixS16_t mtx_divMatrixElemFloat(mtx_matrixFloat_t matrixL, mtx_matrixFloat_t matrixR)
{
	int i, j;
	mtx_matrixS16_t resultMatrix;

	if(matrixL.nLines != matrixR.nLines || matrixL.nCols != matrixR.nCols)
	{
		printf("\nERRO: mtx_divMatrixElemFloat - O numero linhas e colunas devem ser iguais entre as duas matrizes.");
		return resultMatrix;
	}

	resultMatrix = mtx_createMatrixS16(matrixL.nLines, matrixL.nCols);

	for(i = 0; i < resultMatrix.nLines; i++)
		for(j = 0; j < resultMatrix.nCols; j++)
			resultMatrix.mtx[i][j] = (uint16_t) roundf(matrixL.mtx[i][j] / matrixR.mtx[i][j]);

	return resultMatrix;
}

mtx_matrixS16_t mtx_subMatrixS16(mtx_matrixS16_t matrixL, mtx_matrixS16_t matrixR)
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

	resultMatrix = mtx_createMatrixS16(iMax, jMax);

	if(resultMatrix.mtx != NULL)
		for(i = 0; i < iMax; i++)
			for(j = 0; j < jMax; j++)
				resultMatrix.mtx[i][j] = abs(matrixL.mtx[i][j] - matrixR.mtx[i][j]);

	return resultMatrix;
}

bool mtx_equals(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalLimiar)
{
	int i,j;

	if(matrix1.nLines != matrix2.nLines || matrix1.nCols != matrix2.nCols)
		return false;

	for(i = 0; i < matrix1.nLines; i++)
		for(j = 0; j < matrix2.nCols; j++)
			if((matrix1.mtx[i][j] - matrix2.mtx[i][j]) > equalLimiar)
			{
				return false;
			}

	return true;
}

mtx_matrixFloat_t mtx_convertS16ToFloatMatrix(mtx_matrixS16_t originalMatrix)
{
	mtx_matrixFloat_t resultMatrix = mtx_createMatrixFloat(originalMatrix.nLines, originalMatrix.nCols);
	int i,j;

	for(i = 0; i < originalMatrix.nLines; i++)
		for(j = 0; j < originalMatrix.nCols; j++)
			resultMatrix.mtx[i][j] = (float) originalMatrix.mtx[i][j];

	return resultMatrix;
}

mtx_arrayS16_t mtx_zigZagCompressMatrix(mtx_matrixS16_t matrixToCompress)
{
	int i = 0,j = 0, k, lastNonZeroIndex = -1;
	bool down = false;
	mtx_arrayS16_t resultArray;
	mtx_arrayS16_t auxArray = mtx_createArrayS16(matrixToCompress.nLines*matrixToCompress.nCols);
	mtx_matrixS16_t matrix = mtx_createMatrixS16(matrixToCompress.nLines,matrixToCompress.nCols);


	for(k = 0; k < auxArray.size; k++)
	{
		if( i >= matrixToCompress.nLines || j >= matrixToCompress.nCols )
		{
			printf("\nmtx_zigZagCompressMatrix - ERRO: Tentando acessar alem de n ou m, [%d][%d]", i, j);
			break;
		}

		auxArray.array[k] = matrixToCompress.mtx[i][j]; /* Salva todos os elementos da matriz na sequencia de Zig e Zag. */
		if(auxArray.array[k] != 0)
			lastNonZeroIndex = k; /* Registra a ultima posicao que um elemento nao-zero apareceu. */

		if(down) /* Se estah decendo, decide para onde "vai" */
		{
			if( (j-1) < 0 || (i+1) >= matrixToCompress.nLines) /* Se estiver na coluna 0 ou estiver na linha n nao pode descer mais na diagonal */
			{
				/* Entao tenta descer para baixo */
				if( (i+1) >= matrixToCompress.nLines ) /* Se estah na linha n, nao pode mais descer reto. */
				{
					/* Entao vai para a direita */
					j++;
				}
				else /* Se NAO estah na linha n, pode descer para baixo */
				{
					i++;
				}

				/* Decendo para baixo ou indo para a direita, começa a subir */
				down = false;
			}
			else /* Se NAO estiver na coluna 0 pode descer mais na diagonal */
			{
				i++;
				j--;
			}
		}
		else /* Se estah subindo, decide para onde "vai" */
		{
			if( (i-1) < 0 || (j+1) >= matrixToCompress.nCols) /* Se estiver na linha 0 ou na coluna m nao pode subir mais, entao tenta ir para a direita ou para baixo. */
			{
				if( (j+1) >= matrixToCompress.nCols ) /* Se NAO pode ir mais para direita */
				{
					i++;
				}
				else /* Se pode ir para direita vai */
				{
					j++;
				}

				/* Indo para a direita ou para baixo, começa a descer. */
				down = true;
			}
			else /* Se pode subir mais uma linha (i-1), entao sobe na diagonal */
			{
				i--;
				j++;
			}
		}
	}

	/* Armazena apenas os elementos nao nulos no arrayResultante. */
	resultArray = mtx_createArrayS16(lastNonZeroIndex+1);
	for( i = 0; i < resultArray.size; i++)
		resultArray.array[i] = auxArray.array[i];

	mtx_freeArrayS16(auxArray);

	return resultArray;
}

mtx_matrixS16_t mtx_zigZagDecompressMatrix(mtx_arrayS16_t arrayToDecompress, int nLines, int nCols)
{
	int i = 0,j = 0, k;
	bool down = false;
	mtx_matrixS16_t resultMatrix = mtx_createMatrixS16(nLines, nCols);

	for(k = 0; k < arrayToDecompress.size; k++)
	{
		if( i >= resultMatrix.nLines || j >= resultMatrix.nCols )
		{
			printf("\nmtx_zigZagDecompressMatrix - ERRO: Tentando acessar alem de nLines ou nCols, [%d][%d]", i, j);
			break;
		}

		/* Como a matriz eh inicializada com 0s, eh necessario apenas preencher as posicoes nao zero. */
		resultMatrix.mtx[i][j] = arrayToDecompress.array[k];

		if(down) /* Se estah decendo, decide para onde "vai" */
		{
			if( (j-1) < 0 || (i+1) >= resultMatrix.nLines) /* Se estiver na coluna 0 ou estiver na linha n nao pode descer mais na diagonal */
			{
				/* Entao tenta descer para baixo */
				if( (i+1) >= resultMatrix.nLines ) /* Se estah na linha n, nao pode mais descer reto. */
				{
					/* Entao vai para a direita */
					j++;
				}
				else /* Se NAO estah na linha n, pode descer para baixo */
				{
					i++;
				}

				/* Decendo para baixo ou indo para a direita, começa a subir */
				down = false;
			}
			else /* Se NAO estiver na coluna 0 pode descer mais na diagonal */
			{
				i++;
				j--;
			}
		}
		else /* Se estah subindo, decide para onde "vai" */
		{
			if( (i-1) < 0 || (j+1) >= resultMatrix.nCols) /* Se estiver na linha 0 ou na coluna m nao pode subir mais, entao tenta ir para a direita ou para baixo. */
			{
				if( (j+1) >= resultMatrix.nCols ) /* Se NAO pode ir mais para direita */
				{
					i++;
				}
				else /* Se pode ir para direita vai */
				{
					j++;
				}

				/* Indo para a direita ou para baixo, começa a descer. */
				down = true;
			}
			else /* Se pode subir mais uma linha (i-1), entao sobe na diagonal */
			{
				i--;
				j++;
			}
		}
	}

	return resultMatrix;
}

void mtx_printMatrixS16(mtx_matrixS16_t matrixToPrint)
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

void mtx_printArrayS16(mtx_arrayS16_t arrayToPrint)
{
	int i;

	printf("\nArray[%d]: ", arrayToPrint.size);
	for(i = 0; i < arrayToPrint.size; i++)
		printf("%d ", arrayToPrint.array[i]);
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
