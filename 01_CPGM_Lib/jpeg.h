/*
 * @file jpeg.h
 * @author Rafael B. Januzi (rjanuzi@gmail.com)
 * @version 0.1
 */

#ifndef JPEG_H_
#define JPEG_H_

#include <matrix.h>

#define JPEG_DCT_BLOCK_SIZE		8

/**
 * Cria a matriz DCT (T-Matrix) seguindo padrao de matrizes
 * definido por \ref matrix.h
 *
 * @return mtx_matrixFloat_t
 * 	Matriz DCT
 */
mtx_matrixFloat_t jpeg_createDctMatrixT();

/**
 * Cria a matriz DCT de qualidade 50% seguindo padrao de matrizes
 * definido por \ref matrix.h
 *
 * @return mtx_matrixFloat_t
 * 	Matriz Q50
 */
mtx_matrixFloat_t jpeg_createDctMatrixQ50();

/**
 * Calcula a matriz D para um determinado bloco de imagem 8x8.
 *
 * @param \ref mtx_matrixFloat_t originalMatrix
 * 	Bloco 8x8 da imagem original. (Sem qualquer alteracao!)
 *
 * @return mtx_matrixFloat_t
 * 	Matriz D = T*M*T'
 */
mtx_matrixFloat_t jpeg_calcMatrixD(mtx_matrixFloat_t originalMatrix);

mtx_matrixFloat_t jpeg_createTestMatrixOriginal();

#endif /* JPEG_H_ */
