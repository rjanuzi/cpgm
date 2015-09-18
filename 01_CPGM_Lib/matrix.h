#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
	int nLines;
	int nCols;
	uint8_t** mtx;
} mtx_matrix8_t;

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
mtx_matrix8_t mtx_createMatrix8(int nLines, int nCols);

/**
 * Desaloca a memoria alocada para a matriz.
 *
 * @param \ref mtx_matrix8_t matrixToFree
 *	Matriz para desalocar.
 */
void mtx_freeMatrix8(mtx_matrix8_t matrixToFree);

/**
 * Soma um escalar a cada elemento da matriz de 8 bits
 *
 * @param \ref mtx_matrix8_t matrixUpdate
 *	Matriz para atualizar.
 *
 * @param \ref int scalar
 * 	Valor para somar a matriz.
 */
void mtx_sumScalar8(mtx_matrix8_t matrixUpdate, int scalar);

/**
 * Calcula a subtracao de duas matrizes: matrixL - matrixR.
 *
 * Obs.: A subtracao pode ser feita com matrizes de tamanhos diferentes,
 * porem as subtracoes seram realizadas apenas em posicoes (i,j) onde i,j
 * estao definidos em ambas matrizes e a matriz resultante terah tamanho
 * min(iL, iR) x min(jL, jR).
 *
 * @param mtx_matrix8_t matrixL
 * 	Primeira matriz da equacao.
 *
 * @param mtx_matrix8_t matrixR
 * 	Segunda matriz da equacao.
 *
 * @return \ref mtx_matrix8_t
 * 	Retorna uma nova matriz com o resultado.
 *
 */
mtx_matrix8_t mtx_subMatrix8(mtx_matrix8_t matrixL, mtx_matrix8_t matrixR);

/**
 * Imprime na tela os dados dados de uma matriz.
 *
 * @param \ref mtx_matrix8_t matrixToPrint
 *	Matriz para imprimir.
 */
void mtx_printMatrix8(mtx_matrix8_t matrixToPrint);

#endif /* MATRIX_H_ */
