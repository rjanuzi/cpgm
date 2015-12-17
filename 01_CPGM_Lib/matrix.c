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
			newMatrix.mtx[i] = malloc(nCols*sizeof(int16_t));
			if(newMatrix.mtx[i] == NULL)
			{
				printf("\nERRO - mtx_createMatrixS16: Nao foi possivel alocar a memoria necessaria.");
				break;
			}
			else
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

mtx_arrayFloat_t mtx_createArrayFloat(int size)
{
	int i;
	mtx_arrayFloat_t newArray;

	newArray.size = size;

	newArray.array = malloc(size*sizeof(float));

	if(newArray.array != NULL)
		for(i = 0; i < size; i++)
		{
			newArray.array[i] = 0.0;
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
			newMatrix.mtx[i] = malloc(nCols*sizeof(float));
			for( j = 0; j < nCols; j++)
				newMatrix.mtx[i][j] = 0.0;
		}

	return newMatrix;
}

mtx_matrixFloat_t mtx_cpyMatrixFloat(mtx_matrixFloat_t matrixToCpy)
{
	mtx_matrixFloat_t newMatrix;
	int i, j;

	newMatrix = mtx_createMatrixFloat(matrixToCpy.nLines, matrixToCpy.nCols);

	for(i = 0; i < newMatrix.nLines; i++)
		for(j = 0; j < newMatrix.nCols; j++)
			newMatrix.mtx[i][j] = matrixToCpy.mtx[i][j];

	return newMatrix;
}

mtx_matrixS16_t mtx_cpyMatrixS16(mtx_matrixS16_t matrixToCpy)
{
	mtx_matrixS16_t newMatrix;
	int i, j;

	newMatrix = mtx_createMatrixS16(matrixToCpy.nLines, matrixToCpy.nCols);

	for(i = 0; i < newMatrix.nLines; i++)
		for(j = 0; j < newMatrix.nCols; j++)
			newMatrix.mtx[i][j] = matrixToCpy.mtx[i][j];

	return newMatrix;
}

mtx_arrayFloat_t mtx_cpyArrayFloat(mtx_arrayFloat_t arrayToCpy)
{
	mtx_arrayFloat_t newArray;
	int i;

	newArray = mtx_createArrayFloat(arrayToCpy.size);

	for(i = 0; i < newArray.size; i++)
		newArray.array[i] = arrayToCpy.array[i];

	return newArray;
}

mtx_arrayS16_t mtx_cpyArrayS16(mtx_arrayS16_t arrayToCpy)
{
	mtx_arrayS16_t newArray;
	int i;

	newArray = mtx_createArrayS16(arrayToCpy.size);

	for(i = 0; i < newArray.size; i++)
		newArray.array[i] = arrayToCpy.array[i];

	return newArray;
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

void mtx_freeArrayFloat(mtx_arrayFloat_t arrayToFree)
{
	free(arrayToFree.array);
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
				if(matrixL.mtx[i][j] >= matrixR.mtx[i][j])
					resultMatrix.mtx[i][j] = matrixL.mtx[i][j] - matrixR.mtx[i][j];
				else
					resultMatrix.mtx[i][j] = matrixR.mtx[i][j] - matrixL.mtx[i][j];

	return resultMatrix;
}

bool mtx_equalsPaP(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalLimiar)
{
	int i,j, val1, val2;

	if(matrix1.nLines != matrix2.nLines || matrix1.nCols != matrix2.nCols)
		return false;

	for(i = 0; i < matrix1.nLines; i++)
		for(j = 0; j < matrix2.nCols; j++)
		{
			val1 = abs(matrix1.mtx[i][j]);
			val2 = abs(matrix2.mtx[i][j]);

			if( val1 > val2 )
			{
				if((val1 - val2) > equalLimiar)
				{
					return false;
				}
			}
			else
			{
				if((val2 - val1) > equalLimiar)
				{
					return false;
				}
			}
		}

	return true;
}

bool mtx_equalsMean(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalLimiar)
{
	int i,j;
	int media1 = 0, media2 = 0;

	if(matrix1.nLines != matrix2.nLines || matrix1.nCols != matrix2.nCols)
		return false;

	for(i = 0; i < matrix1.nLines; i++)
		for(j = 0; j < matrix2.nCols; j++)
		{
			media1 += matrix1.mtx[i][j];
			media2 += matrix2.mtx[i][j];
		}

	media1 /= (matrix1.nLines*matrix1.nCols);
	media2 /= (matrix1.nLines*matrix1.nCols);

	media1 = abs(media1);
	media2 = abs(media2);

	if(media1 > media2)
	{
		if((media1 - media2) <= equalLimiar)
		{
			return true;
		}
	}
	else
	{
		if((media2 - media1) <= equalLimiar)
		{
			return true;
		}
	}

	return false;
}

bool mtx_equalsPercentage(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalValorLimiar, float equalLimiarPercentage)
{
	int i,j, val1 = 0, val2 = 0, numberOfEqualPixels = 0;
	float percentageOfEqualsPixels = 0.0;

	if(matrix1.nLines != matrix2.nLines || matrix1.nCols != matrix2.nCols)
		return false;

	for(i = 0; i < matrix1.nLines; i++)
		for(j = 0; j < matrix2.nCols; j++)
		{
			val1 = abs(matrix1.mtx[i][j]);
			val2 = abs(matrix2.mtx[i][j]);

			if( val1 > val2 )
			{
				if((val1 - val2) <= equalValorLimiar)
				{
					percentageOfEqualsPixels++;
				}
			}
			else
			{
				if((val2 - val1) <= equalValorLimiar)
				{
					percentageOfEqualsPixels++;
				}
			}
		}

	numberOfEqualPixels = percentageOfEqualsPixels;
	percentageOfEqualsPixels /= (matrix1.nLines*matrix2.nCols);
	percentageOfEqualsPixels *= 100;

	if(percentageOfEqualsPixels >= equalLimiarPercentage)
		return true;

	return false;
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

void mtx_printArrayFloat(mtx_arrayFloat_t arrayToPrint)
{
	int i;

	printf("\nArray[%d]: ", arrayToPrint.size);
	for(i = 0; i < arrayToPrint.size; i++)
		printf("%.2f ", arrayToPrint.array[i]);
}

void mtx_printMatrixFloat(mtx_matrixFloat_t matrixToPrint)
{
	int i,j;

	printf("\nMatrix[%d][%d]: ", matrixToPrint.nLines, matrixToPrint.nCols);
	for(i = 0; i < matrixToPrint.nLines; i++)
	{
		printf("\n");
		for(j = 0; j < matrixToPrint.nCols; j++)
			printf(" %.2f", matrixToPrint.mtx[i][j]);
	}
}

mtx_pos_t* mtx_getVizinhos4(mtx_pos_t centerPixelPosition, int maxLineVal , int maxColVal)
{
	mtx_pos_t* posicoes;

	if(centerPixelPosition.lineIndex < 0 || centerPixelPosition.colIndex < 0)
	{
		printf("\nERRO - mtx_getVizinhos4 - posicao de pixel passada com parametro invalido!");
		return NULL;
	}

	posicoes = malloc(4*sizeof(mtx_pos_t));

	if(posicoes == NULL)
	{
		printf("\nERRO - mtx_getVizinhos4 - Problema na alocacao de memoria para o array de posicoes!");
		return NULL;
	}

	/*
	 *	X  | V1 | X
	 *	V2 | P  | V3
	 *	X  | V4 | X
	 */

	/* V1 */
	posicoes[0].lineIndex = (centerPixelPosition.lineIndex-1);
	if(posicoes[0].lineIndex < 0)
		posicoes[0].colIndex = -1; /* Nao existe vizinho a cima */
	else
		posicoes[0].colIndex = centerPixelPosition.colIndex;

	/* V2 */
	posicoes[1].colIndex = (centerPixelPosition.colIndex-1);
	if(posicoes[1].colIndex < 0)
		posicoes[1].lineIndex = -1; /* Nao existe vizinho a esquerda */
	else
		posicoes[1].lineIndex = centerPixelPosition.lineIndex;

	/* V3 */
	posicoes[2].colIndex = (centerPixelPosition.colIndex+1);
	if(posicoes[2].colIndex > maxColVal)
		posicoes[2].colIndex = -1;

	if(posicoes[2].colIndex < 0)
		posicoes[2].lineIndex = -1; /* Nao existe vizinho a direita */
	else
		posicoes[2].lineIndex = centerPixelPosition.lineIndex;

	/* V4 */
	posicoes[3].lineIndex = (centerPixelPosition.lineIndex+1);
	if(posicoes[3].lineIndex > maxLineVal)
		posicoes[3].lineIndex = -1;

	if(posicoes[3].lineIndex < 0)
		posicoes[3].colIndex = -1;
	else
		posicoes[3].colIndex = centerPixelPosition.colIndex;

	return &posicoes[0];
}

mtx_pos_t* mtx_getVizinhos8(mtx_pos_t centerPixelPosition, int maxLineVal, int maxColVal)
{
	mtx_pos_t* posicoes;

	if(centerPixelPosition.lineIndex < 0 || centerPixelPosition.colIndex < 0)
	{
		printf("\nERRO - mtx_getVizinhos4 - posicao de pixel passada com parametro invalido!");
		return NULL;
	}

	posicoes = malloc(8*sizeof(mtx_pos_t));

	if(posicoes == NULL)
	{
		printf("\nERRO - mtx_getVizinhos4 - Problema na alocacao de memoria para o array de posicoes!");
		return NULL;
	}

	/*
	 *	V1 | V2 | V3
	 *	V4 | P  | V5
	 *	V6 | V7 | V8
	 */

	/* V1 */
	posicoes[0].lineIndex = (centerPixelPosition.lineIndex-1);
	if(posicoes[0].lineIndex < 0)
		posicoes[0].colIndex = -1;
	else
	{
		posicoes[0].colIndex = (centerPixelPosition.colIndex-1);
		if(posicoes[0].colIndex < 0)
			posicoes[0].lineIndex = -1;
	}

	/* V2 */
	posicoes[1].lineIndex = (centerPixelPosition.lineIndex-1);
	if(posicoes[1].lineIndex < 0)
		posicoes[1].colIndex = -1;
	else
		posicoes[1].colIndex = centerPixelPosition.colIndex;

	/* V3 */
	posicoes[2].colIndex = (centerPixelPosition.colIndex+1);
	if(posicoes[2].colIndex > maxColVal)
	{
		posicoes[2].lineIndex = -1;
		posicoes[2].colIndex = -1;
	}
	else
	{
		posicoes[2].lineIndex = (centerPixelPosition.lineIndex-1);
		if(posicoes[2].lineIndex < 0)
		{
			posicoes[2].lineIndex = -1;
			posicoes[2].colIndex = -1;
		}
	}

	/* V4 */
	posicoes[3].colIndex = (centerPixelPosition.colIndex-1);
	if(posicoes[3].colIndex < 0)
		posicoes[3].lineIndex = -1;
	else
		posicoes[3].lineIndex = centerPixelPosition.lineIndex;

	/* V5 */
	posicoes[4].colIndex = (centerPixelPosition.colIndex+1);
	if(posicoes[4].colIndex > maxColVal)
	{
		posicoes[4].lineIndex = -1;
		posicoes[4].colIndex = -1;
	}
	else
		posicoes[4].lineIndex = centerPixelPosition.lineIndex;

	/* V6 */
	posicoes[5].lineIndex = (centerPixelPosition.lineIndex+1);
	if(posicoes[5].lineIndex > maxLineVal)
	{
		posicoes[5].lineIndex = -1;
		posicoes[5].colIndex = -1;
	}
	else
	{
		posicoes[5].colIndex = (centerPixelPosition.colIndex-1);
		if(posicoes[5].colIndex < 0)
		{
			posicoes[5].lineIndex = -1;
			posicoes[5].colIndex = -1;
		}
	}

	/* V7 */
	posicoes[6].lineIndex = (centerPixelPosition.lineIndex+1);
	if(posicoes[6].lineIndex > maxLineVal)
	{
		posicoes[6].lineIndex = -1;
		posicoes[6].colIndex = -1;
	}
	else
		posicoes[6].colIndex = centerPixelPosition.colIndex;

	/* V8 */
	posicoes[7].lineIndex = (centerPixelPosition.lineIndex+1);
	if(posicoes[7].lineIndex > maxLineVal)
	{
		posicoes[7].lineIndex = -1;
		posicoes[7].colIndex = -1;
	}
	else
	{
		posicoes[7].colIndex = (centerPixelPosition.colIndex+1);
		if(posicoes[7].colIndex > maxColVal)
		{
			posicoes[7].lineIndex = -1;
			posicoes[7].colIndex = -1;
		}
	}

	return &posicoes[0];
}

bool mtx_equalsArrayFloat(mtx_arrayFloat_t array1, mtx_arrayFloat_t array2)
{
	int i;

	if(array1.size != array2.size)
		return false;

	for(i = 0; i < array1.size; i++)
		if(array1.array[i] != array2.array[i])
			return false;

	return true;
}

mtx_arrayFloat_t mtx_addToBack(mtx_arrayFloat_t originalArray, mtx_arrayFloat_t valuesToAdd)
{
	mtx_arrayFloat_t novoArray;
	int i, j;

	novoArray = mtx_createArrayFloat(originalArray.size+valuesToAdd.size);

	for(i = 0; i < originalArray.size; i++)
		novoArray.array[i] = originalArray.array[i];

	j = 0;
	for( ; i < novoArray.size; i++)
		novoArray.array[i] = valuesToAdd.array[j++];

	return novoArray;
}

mtx_matrixFloat_t mtx_addCols(mtx_matrixFloat_t originalMatrix, int numberOfCols)
{
	mtx_matrixFloat_t newMatrix;
	int i, j;

	newMatrix = mtx_createMatrixFloat(originalMatrix.nLines, originalMatrix.nCols+numberOfCols);

	/* Copia os valores ja existentes da matriz A */
	for(i = 0; i < originalMatrix.nLines; i++)
		for(j = 0; j < originalMatrix.nCols; j++)
			newMatrix.mtx[i][j] = originalMatrix.mtx[i][j];

	/* Para todas as linhas colocar os valores das novas linhas. */
	/* Coloca 0 em todas as novas colunas */
	for(i = 0; i < originalMatrix.nLines; i++)
		for(j = originalMatrix.nCols; j < newMatrix.nCols; j++)
			newMatrix.mtx[i][j] = 0;

	return newMatrix;
}
