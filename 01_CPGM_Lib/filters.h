/*
 * filters.h
 *
 *  Created on: Oct 1, 2015
 *      Author: Rafael
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include <matrix.h>

/**
 * Retorna uma matriz 3x3 com a mascara de laplaciano:
 *
 * | -1 | -4 | -1 |
 * | -4 | 20 | -4 |
 * | -1 | -4 | -1 |
 *
 *	@return \ref mtx_matrixS16_t
 *		Retorna a matriz da mascara Laplaciano.
 *
 */
mtx_matrixS16_t flt_getLaplacianoMask();

/**
 * Retorna uma matriz 3x3 com a mascara de medias:
 *
 * | 1/9 | 1/9 | 1/9 |
 * | 1/9 | 1/9 | 1/9 |
 * | 1/9 | 1/9 | 1/9 |
 *
 *	@return \ref mtx_matrixFloat_t
 *		Retorna a matriz da mascara media.
 *
 */
mtx_matrixFloat_t flt_getMeanMask();

#endif /* FILTERS_H_ */
