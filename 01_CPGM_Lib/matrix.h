/**
 * @file matrix.h
 * @author Rafael B. Januzi (rjanuzi@gmail.com)
 * @version 0.1
 *
 * Este arquivo juntamento com o arquivo \ref matrix.c fornece um conjunto de funcoes
 * para manipulacao de matrizes dinamicamente alocadas.
 *
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
	int nLines;
	int nCols;
	int16_t** mtx;
} mtx_matrixS16_t;

typedef struct {
	int size;
	int16_t* array;
} mtx_arrayS16_t;

typedef struct {
	int size;
	float* array;
} mtx_arrayFloat_t;

typedef struct {
	int nLines;
	int nCols;
	float** mtx;
} mtx_matrixFloat_t;

typedef struct {
	int lineIndex;
	int colIndex;
} mtx_pos_t;

/**
 *	Instancia uma matriz com elementos de 2 Bytes (int16_t).
 *
 *	@param \ref int nLines
 *		Numero de linhas da matriz.
 *	@param int nCols
 *		Numero de colunas da matriz.
 *
 *	@return mtx_matrixS16_t
 *		Matriz nLines x nCols alocada.
 *
 *	 Obs.: O acesso eh feito matrix.mtx[i][j].
 */
mtx_matrixS16_t mtx_createMatrixS16(int nLines, int nCols);

/**
 *	Instancia um array com elementos de 2 Bytes (int16_t).
 *
 *	@param \ref int size
 *		Tamanho do array.
 *
 *	@return mtx_arrayS16_t
 *		Array de tamanho size alocado.
 *
 *	 Obs.: O acesso eh feito normalmente matrix.array[i][j].
 */
mtx_arrayS16_t mtx_createArrayS16(int size);

/**
 *	Instancia um array com elementos floats.
 *
 *	@param \ref int size
 *		Tamanho do array.
 *
 *	@return mtx_arrayFloat_t
 *		Array de tamanho size alocado.
 *
 *	 Obs.: O acesso eh feito normalmente matrix.array[i][j].
 */
mtx_arrayFloat_t mtx_createArrayFloat(int size);

/**
 *	Instancia uma matriz com elementos de reais (float).
 *
 *	@param \ref int nLines
 *		Numero de linhas da matriz.
 *	@param int nCols
 *		Numero de colunas da matriz.
 *
 *	@return
 *		Matriz nLines x nCols alocada.
 *
 *	 Obs.: O acesso eh feito matrix.mtx[i][j].
 */
mtx_matrixFloat_t mtx_createMatrixFloat(int nLines, int nCols);


/**
 * Cria uma copia de uma matriz
 *
 * @param mtx_matrixFloat_t matrixToCpy
 *		Matriz para ser copiada.
 *
 *	@return
 *		Copia da matriz passada por parametro.
 */
mtx_matrixFloat_t mtx_cpyMatrixFloat(mtx_matrixFloat_t matrixToCpy);

/**
 * Cria uma copia de uma matriz
 *
 * @param mtx_matrixS16_t matrixToCpy
 *		Matriz para ser copiada.
 *
 *	@return
 *		Copia da matriz passada por parametro.
 */
mtx_matrixS16_t mtx_cpyMatrixS16(mtx_matrixS16_t matrixToCpy);

/**
 * Cria uma copia de um array.
 *
 * @param mtx_arrayFloat_t arrayToCpy
 *		Array para ser copiado.
 *
 *	@return
 *		Copia do array passada por parametro.
 */
mtx_arrayFloat_t mtx_cpyArrayFloat(mtx_arrayFloat_t arrayToCpy);

/**
 * Cria uma copia de um array.
 *
 * @param mtx_array16_t arrayToCpy
 *		Array para ser copiado.
 *
 *	@return
 *		Copia do array passada por parametro.
 */
mtx_arrayS16_t mtx_cpyArrayS16(mtx_arrayS16_t arrayToCpy);

/**
 * Desaloca a memoria alocada para a matriz.
 *
 * @param \ref mtx_matrixS16_t matrixToFree
 *	Matriz para desalocar.
 */
void mtx_freeMatrixS16(mtx_matrixS16_t matrixToFree);

/**
 * Desaloca a memoria alocada para o array.
 *
 * @param \ref mtx_arrayS16_t arrayToFree
 *	Array para desalocar.
 */
void mtx_freeArrayS16(mtx_arrayS16_t arrayToFree);

/**
 * Desaloca a memoria alocada para o array.
 *
 * @param \ref mtx_arrayFloat_t arrayToFree
 *	Array para desalocar.
 */
void mtx_freeArrayFloat(mtx_arrayFloat_t arrayToFree);

/**
 * Desaloca a memoria alocada para a matriz.
 *
 * @param \ref mtx_matrixFloat_t matrixToFree
 *	Matriz para desalocar.
 */
void mtx_freeMatrixFloat(mtx_matrixFloat_t matrixToFree);

/**
 * Soma um escalar a cada elemento da matriz de 16 bits
 *
 * @param \ref mtx_matrixS16_t matrixUpdate
 *	Matriz para atualizar.
 *
 * @param \ref int scalar
 * 	Valor para somar a matriz.
 */
void mtx_sumScalarS16(mtx_matrixS16_t matrixToUpdate, int scalar);

/**
 * Soma um escalar a cada elemento da matriz de floats
 *
 * @param \ref mtx_matrixFloat_t matrixUpdate
 *	Matriz para atualizar.
 *
 * @param \ref int scalar
 * 	Valor para somar a matriz.
 */
void mtx_sumScalarFloat(mtx_matrixFloat_t matrixToUpdate, float scalar);

/**
 * Multiplica um escalar a cada elemento da matriz de 16 bits
 *
 * @param \ref mtx_matrixFloat_t matrixUpdate
 *	Matriz para atualizar.
 *
 * @param \ref int scalar
 * 	Valor para multiplicar com a matriz.
 */
void mtx_multScalarFloat(mtx_matrixFloat_t matrixToUpdate, float scalar);

/**
 * Realiza a transposicao da matriz passada por parametro.
 *
 * @param \ref mtx_matrixFloat_t matrixToUpdate
 *		Matriz para a qual a transposta deve ser calculada.
 *
 * @return \ref mtx_matrixFloat_t
 * 	Transposta da matriz passada por parametro.
 */
mtx_matrixFloat_t mtx_transposeMtxFloat(mtx_matrixFloat_t matrixToTranspose);

/**
 * Calcula o produto de duas matrizes: matrixL * matrixR.
 *
 * @param mtx_matrixFloat_t matrixL
 * 	Primeira matriz da equacao.
 *
 * @param mtx_matrixFloat_t matrixR
 * 	Segunda matriz da equacao.
 *
 * @return \ref mtx_matrixFloat_t
 * 	Retorna uma nova matriz com o resultado.
 *
 */
mtx_matrixFloat_t mtx_prodMatrixFloat(mtx_matrixFloat_t matrixL, mtx_matrixFloat_t matrixR);

/**
 * Calcula a divisao de cada elemento de uma matriz pelo elemento correspondente de outra
 * matriz.
 *
 * 	Formula: Ci,j = round(Di,j / Qi,j)
 *
 * @param mtx_matrixFloat_t matrixL
 * 	Primeira matriz da equacao.
 *
 * @param mtx_matrixFloat_t matrixR
 * 	Segunda matriz da equacao.
 *
 * @return \ref mtx_matrixS16_t
 * 	Retorna uma nova matriz com o resultado.
 *
 */
mtx_matrixS16_t mtx_divMatrixElemFloat(mtx_matrixFloat_t matrixL, mtx_matrixFloat_t matrixR);

/**
 * Calcula a subtracao de duas matrizes: matrixL - matrixR.
 *
 * Obs.: A subtracao pode ser feita com matrizes de tamanhos diferentes,
 * porem as subtracoes seram realizadas apenas em posicoes (i,j) onde i,j
 * estao definidos em ambas matrizes e a matriz resultante terah tamanho
 * min(iL, iR) x min(jL, jR).
 *
 * @param mtx_matrixS16_t matrixL
 * 	Primeira matriz da equacao.
 *
 * @param mtx_matrixS16_t matrixR
 * 	Segunda matriz da equacao.
 *
 * @return \ref mtx_matrixS16_t
 * 	Retorna uma nova matriz com o resultado.
 *
 */
mtx_matrixS16_t mtx_subMatrixS16(mtx_matrixS16_t matrixL, mtx_matrixS16_t matrixR);

/**
 * Verifica se duas matrizes sao iguais, as matrizes sao comparadas posicao por
 * posicao.
 *
 * Obs.: Matrizes de tamanho diferentes sao automaticamente consideradas
 * diferentes.
 *
 * @param mtx_matrixS16_t matrix1
 * 	Primeira matriz para comparar.
 *
 * @param mtx_matrixS16_t matrix2
 * 	Segunda matriz para comparar.
 *
 * @param uint8_t equalLimiar
 * 	Valor limite para considerar pixels como iguais iguais, caso a subtracao de algum
 * 	pixel da matriz1 e o pixel correspondente da matriz2 for <= que equalLimiar
 * 	as matrizes seram consideradas diferentes.
 *
 * @return \ref bool
 * 	Retorn true se as matrizes forem iguais e false se forem diferentes.
 *
 */
bool mtx_equalsPaP(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalLimiar);

/**
 * Verifica se duas matrizes sao iguais, as matrizes sao comparadas considerando uma média
 * dos valores nas matriz.
 *
 * Obs.: Matrizes de tamanho diferentes sao automaticamente consideradas
 * diferentes.
 *
 * @param mtx_matrixS16_t matrix1
 * 	Primeira matriz para comparar.
 *
 * @param mtx_matrixS16_t matrix2
 * 	Segunda matriz para comparar.
 *
 * @param uint8_t equalLimiar
 * 	Valor limite para considerar pixels como iguais iguais, caso a subtracao de algum
 * 	pixel da matriz1 e o pixel correspondente da matriz2 for <= que equalLimiar
 * 	as matrizes seram consideradas diferentes.
 *
 * @return \ref bool
 * 	Retorn true se as matrizes forem iguais e false se forem diferentes.
 *
 */
bool mtx_equalsMean(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalLimiar);

/**
 * Verifica se duas matrizes sao iguais, para comparar as matrizes eh gerada uma porcentagem
 * de pixels iguais entre as duas. Os pixels sao considerados iguais se a diferenca entre eles
 * estiver a baixo de um limiar.
 *
 * Obs.: Matrizes de tamanho diferentes sao automaticamente consideradas
 * diferentes.
 *
 * @param mtx_matrixS16_t matrix1
 * 	Primeira matriz para comparar.
 *
 * @param mtx_matrixS16_t matrix2
 * 	Segunda matriz para comparar.
 *
 * @param int equalValorLimiar
 * 	Valor do limiar para diferencia pixels.
 *
 * @param uint8_t equalLimiarPercentage
 * 	Valor limite para considerar matrizes iguais, ou seja para um limiar de 25.0%, tem-se que
 * 	duas matrizes sao iguais se elas tem pelo menos 25.0% dos pixels com o mesmo valor.
 *
 * @return \ref bool
 * 	Retorn true se as matrizes forem iguais e false se forem diferentes.
 *
 */
bool mtx_equalsPercentage(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalValorLimiar, float equalLimiarPercentage);

/**
 * Converte uma matriz com os valores S16 para uma matriz com valores em
 * floats.
 *
 * @param mtx_matrixS16_t originalMatrix
 * 	Matriz a ser convertida.
 *
 * @return \ref mtx_matrixFloat_t
 * 	Matriz gerada.
 *
 */
mtx_matrixFloat_t mtx_convertS16ToFloatMatrix(mtx_matrixS16_t originalMatrix);

/**
 * Comprime uma matriz para um array, varrendo a matriz em Zig Zag,
 * salvando todos os elementos nao nulos.
 *
 * @param mtx_matrixS16_t matrixToCompress
 * 	Matriz a ser comprimida.
 *
 * @return \ref mtx_arrayS16_t
 * 	Array com os dados nao nulos da matriz lida em Zig Zag.
 *
 */
mtx_arrayS16_t mtx_zigZagCompressMatrix(mtx_matrixS16_t matrixToCompress);

/**
 * Descomprime um array para uma matriz, varrendo a matriz em Zig Zag.
 *
 * Como o array foi gerado com perde dados a partir de uma matriz,
 * ele possui menos valores que a matriz, entao eh necessario passar
 * o tamanho da matriz que deseja-se obter (nLines*nCols), onde os valores
 * seram inseridos em ZigZag e o restante das posicoes seram
 * preenchidas com zeros.
 *
 * @param mtx_arrayS16_t arrayToDecompress
 * 	Array a ser descomprimido.
 *
 * @param int nLines
 * 	Numero de linhas na matriz gerada.
 *
 * @param int nCols
 * 	Numero de colunas na matriz gerada.
 *
 * @return \ref mtx_matrixS16_t
 * 	Matriz resultante da descompressao,
 *
 */
mtx_matrixS16_t mtx_zigZagDecompressMatrix(mtx_arrayS16_t arrayToDecompress, int nLines, int nCols);

/**
 * Imprime na tela os dados de uma matriz.
 *
 * @param \ref mtx_matrixS16_t matrixToPrint
 *	Matriz para imprimir.
 */
void mtx_printMatrixS16(mtx_matrixS16_t matrixToPrint);

/**
 * Imprime na tela os dados de um array.
 *
 * @param \ref mtx_arrayS16_t arrayToPrint
 *	Array para imprimir.
 */
void mtx_printArrayS16(mtx_arrayS16_t arrayToPrint);

/**
 * Imprime na tela os dados de um array.
 *
 * @param \ref mtx_arrayFloat_t arrayToPrint
 *	Array para imprimir.
 */
void mtx_printArrayFloat(mtx_arrayFloat_t arrayToPrint);

/**
 * Imprime na tela os dados de uma matriz.
 *
 * @param \ref mtx_matrixFloat_t matrixToPrint
 *	Matriz para imprimir.
 */
void mtx_printMatrixFloat(mtx_matrixFloat_t matrixToPrint);

/**
 * Retorna um array de quatro posicoes do tipo \ref mtx_pos com as posicoes
 * dos vizinho-4 de um pixel (ponto na matriz).
 *
 * Considerando o pixel de interesse P:
 *
 *	X  | V1 | X
 *	V2 | P  | V3
 *	X  | V4 | X
 *
 * @param mtx_pos centerPixelPosition
 * 	Ponto P de interesse que deseja-se encontrar os vizinho-4.
 *
 * @param int maxLineVal
 * 	Tamanho maximo de linhas da matriz onde o pixel esta inserido.
 *
 * @param int maxColVal
 * 	Tamanho maximo de colunas da matriz onde o pixel esta inserido.
 *
 * @return
 * 	Um array de 4 posicoes \ref mtx_pos com os vizinhos-4 do ponto passado
 * 	por parametro, a ordem dos pontos sao dados da esquerda para a direita
 * 	e de cima para baixo (array: [V1, V2, V3, V4]).
 *
 */
mtx_pos_t* mtx_getVizinhos4(mtx_pos_t centerPixelPosition, int maxLineVal, int maxColVal);

/**
 * Retorna um array de quatro posicoes do tipo \ref mtx_pos com as posicoes
 * dos vizinho-8 de um pixel (ponto na matriz).
 *
 * Considerando o pixel de interesse P:
 *
 *	V1 | V2 | V3
 *	V4 | P  | V5
 *	V6 | V7 | V8
 *
 * @param mtx_pos centerPixelPosition
 * 	Ponto P de interesse que deseja-se encontrar os vizinho-8.
 *
 * @param int maxLineVal
 * 	Tamanho maximo de linhas da matriz onde o pixel esta inserido.
 *
 * @param int maxColVal
 * 	Tamanho maximo de colunas da matriz onde o pixel esta inserido.
 *
 * @return
 * 	Um array de 8 posicoes \ref mtx_pos com os vizinhos-4 do ponto passado
 * 	por parametro, a ordem dos pontos sao dados da esquerda para a direita
 * 	e de cima para baixo (array: [V1, V2, V3, V4, V5, V6, V7, V8]).
 *
 */
mtx_pos_t* mtx_getVizinhos8(mtx_pos_t centerPixelPosition, int maxLineVal, int maxColVal);

/**
 * Verifica se dois array sao iguais.
 *
 * @param mtx_arrayFloat_t array1
 * 	Array 1 para comparar.
 *
 * @param mtx_arrayFloat_t array1
 * 	Array 1 para comparar.
 *
 * 	@return
 * 		True caso sejam iguais e false caso sejam diferentes.
 */
bool mtx_equalsArrayFloat(mtx_arrayFloat_t array1, mtx_arrayFloat_t array2);

/**
 * Adicionar elementos ao final de um array.
 *
 * @param mtx_arrayFloat_t originalArray
 * 	Array original.
 *
 * @param mtx_arrayFloat_t valueToAdd
 * 	Array com os valores para adicionar ao final do array original.
 *
 * @return
 * 	Novo array com os valores originais concatenados com os novos valores.
 */
mtx_arrayFloat_t mtx_addToBack(mtx_arrayFloat_t originalArray, mtx_arrayFloat_t valueToAdd);

/**
 * Adicionar novas colunas ao final da matriz.
 *
 * @param mtx_matrixFloat_t originalMatrix
 * 	Matriz original.
 *
 * @param int numberOfCols
 * 	Numero de novas colunas para adicionar
 *
 * @return mtx_matrixFloat_t
 *	Nova matriz com as colunas adicionadas ao final.
 */
mtx_matrixFloat_t mtx_addCols(mtx_matrixFloat_t originalMatrix, int numberOfCols);

#endif /* MATRIX_H_ */
