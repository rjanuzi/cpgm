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
#include <math.h>

typedef struct {
	int nLines;
	int nCols;
	int16_t** mtx;
} mtx_matrixS16_t;

typedef struct {
	int nLines;
	int nCols;
	float** mtx;
} mtx_matrixFloat_t;

/**
 *	Instancia uma matriz com elementos de 1 Bytes (uint8_t).
 *
 *	@param \ref int nLines
 *		Numero de linhas da matriz.
 *	@param int nCols
 *		Numero de colunas da matriz.
 *
 *	@return
 *		Ponteiro para uma matriz nLines x nCols, cada linha da matriz
 *	 possui um ponteiro para um array de tamanho nCols.
 *
 *	 Obs.: O acesso eh feito normalmente matrix[i][j].
 */
mtx_matrixS16_t mtx_createMatrixU8(int nLines, int nCols);

/**
 *	Instancia uma matriz com elementos de 2 Bytes (int16_t).
 *
 *	@param \ref int nLines
 *		Numero de linhas da matriz.
 *	@param int nCols
 *		Numero de colunas da matriz.
 *
 *	@return
 *		Ponteiro para uma matriz nLines x nCols, cada linha da matriz
 *	 possui um ponteiro para um array de tamanho nCols.
 *
 *	 Obs.: O acesso eh feito normalmente matrix[i][j].
 */
mtx_matrixFloat_t mtx_createMatrixFloat(int nLines, int nCols);

/**
 * Desaloca a memoria alocada para a matriz.
 *
 * @param \ref mtx_matrixS16_t matrixToFree
 *	Matriz para desalocar.
 */
void mtx_freeMatrixU8(mtx_matrixS16_t matrixToFree);

/**
 * Desaloca a memoria alocada para a matriz.
 *
 * @param \ref mtx_matrixFloat_t matrixToFree
 *	Matriz para desalocar.
 */
void mtx_freeMatrixFloat(mtx_matrixFloat_t matrixToFree);

/**
 * Soma um escalar a cada elemento da matriz de 8 bits
 *
 * @param \ref mtx_matrixS16_t matrixUpdate
 *	Matriz para atualizar.
 *
 * @param \ref int scalar
 * 	Valor para somar a matriz.
 */
void mtx_sumScalarU8(mtx_matrixS16_t matrixToUpdate, int scalar);

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
 * Multiplica um escalar a cada elemento da matriz de 8 bits
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
 * @return \ref mtx_matrixFloat_t
 * 	Retorna uma nova matriz com o resultado.
 *
 */
mtx_matrixFloat_t mtx_divMatrixElemFloat(mtx_matrixFloat_t matrixL, mtx_matrixFloat_t matrixR);

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
mtx_matrixS16_t mtx_subMatrixU8(mtx_matrixS16_t matrixL, mtx_matrixS16_t matrixR);

/**
 * Converte uma matriz com os valores U8 para uma matriz com valores em
 * floats.
 *
 * @param mtx_matrixS16_t originalMatrix
 * 	Matriz a ser convertida.
 *
 * @return \ref mtx_matrixFloat_t
 * 	Matriz gerada.
 *
 */
mtx_matrixFloat_t mtx_convertU8ToFloatMatrix(mtx_matrixS16_t originalMatrix);

/**
 * Imprime na tela os dados dados de uma matriz.
 *
 * @param \ref mtx_matrixS16_t matrixToPrint
 *	Matriz para imprimir.
 */
void mtx_printMatrixU8(mtx_matrixS16_t matrixToPrint);

/**
 * Imprime na tela os dados dados de uma matriz.
 *
 * @param \ref mtx_matrixFloat_t matrixToPrint
 *	Matriz para imprimir.
 */
void mtx_printMatrixFloat(mtx_matrixFloat_t matrixToPrint);

#endif /* MATRIX_H_ */
