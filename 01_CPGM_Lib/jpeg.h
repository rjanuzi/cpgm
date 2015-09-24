/*
 * @file jpeg.h
 * @author Rafael B. Januzi (rjanuzi@gmail.com)
 * @version 0.1
 */

#ifndef JPEG_H_
#define JPEG_H_

#include <matrix.h>
#include <pgm.h>

#define JPEG_DCT_BLOCK_SIZE		8

#define JPEG_QUALITY_MATRIX_TO_USE_Q10		1
#define JPEG_QUALITY_MATRIX_TO_USE_Q50		2
#define JPEG_QUALITY_MATRIX_TO_USE_Q90		3

/**
 * Cria a matriz DCT (T-Matrix) seguindo padrao de matrizes
 * definido por \ref matrix.h
 *
 * @return mtx_matrixFloat_t
 * 	Matriz DCT
 */
mtx_matrixFloat_t jpeg_createDctMatrixT8x8();

/**
 * Cria a matriz DCT de qualidade 10% seguindo padrao de matrizes
 * definido por \ref matrix.h
 *
 * @return mtx_matrixFloat_t
 * 	Matriz Q10
 */
mtx_matrixFloat_t jpeg_createDctMatrixQ108x8();

/**
 * Cria a matriz DCT de qualidade 50% seguindo padrao de matrizes
 * definido por \ref matrix.h
 *
 * @return mtx_matrixFloat_t
 * 	Matriz Q50
 */
mtx_matrixFloat_t jpeg_createDctMatrixQ508x8();

/**
 * Cria a matriz DCT de qualidade 90% seguindo padrao de matrizes
 * definido por \ref matrix.h
 *
 * @return mtx_matrixFloat_t
 * 	Matriz Q90
 */
mtx_matrixFloat_t jpeg_createDctMatrixQ908x8();

/**
 * Calcula a matriz D para um determinado bloco de imagem 8x8.
 *
 * @param \ref mtx_matrixFloat_t originalMatrix
 * 	Bloco 8x8 da imagem original. (Sem qualquer alteracao!)
 *
 * @return mtx_matrixFloat_t
 * 	Matriz D = T*M*T'
 */
mtx_matrixFloat_t jpeg_calcMatrixD8x8(mtx_matrixFloat_t originalMatrix);

/**
 * Aplica o algoritmo DCT aa uma imagem pgm.
 *
 * @param \ref pgm_img_t originalPgmImg
 * 	Imagem onde o algoritmo deve ser aplicado.
 *
 * @param \ref uint8_t qualityMatrixToUse
 * 	Seleciona qual matriz de qualidade deve ser utilizada. Utilizar as
 * 	constantes \ref JPEG_QUALITY_MATRIX_TO_USE_Q10, \ref JPEG_QUALITY_MATRIX_TO_USE_Q50
 * 	ou \ref JPEG_QUALITY_MATRIX_TO_USE_Q90
 *
 * @return pgm_img_t
 * 	Retorna uma nova imagem apos a aplicacao do DCT.
 */
pgm_img_t jpeg_applyDctToPgmImg(pgm_img_t originalPgmImg, uint8_t qualityMatrixToUse);

//TODO
//<return> jpeg_compactPgmData(pgm_img_t originalPgmImg);

mtx_matrixFloat_t jpeg_createTestMatrixOriginal8x8();

#endif /* JPEG_H_ */
