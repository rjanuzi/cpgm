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
	int nLines;
	int nCols;
	float** mtx;
} mtx_matrixFloat_t;

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
 * Verifica se duas matrizes sao iguais.
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
 * 	pixel da matriz1 e o pixel correspondente da matriz2 for >= que equalLimiar
 * 	as matrizes seram consideradas diferentes.
 *
 * @return \ref bool
 * 	Retorn true se as matrizes forem iguais e false se forem diferentes.
 *
 */
bool mtx_equals(mtx_matrixS16_t matrix1, mtx_matrixS16_t matrix2, uint8_t equalLimiar);

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
 * Imprime na tela os dados de uma matriz.
 *
 * @param \ref mtx_matrixFloat_t matrixToPrint
 *	Matriz para imprimir.
 */
void mtx_printMatrixFloat(mtx_matrixFloat_t matrixToPrint);

#endif /* MATRIX_H_ */
