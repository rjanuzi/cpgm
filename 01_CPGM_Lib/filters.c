/*
 * filters.c
 *
 *  Created on: Oct 1, 2015
 *      Author: Rafael
 */

#include <filters.h>

const int16_t flt_laplacianoMatrix[3][3] =
{
		{-1, -4, -1},
		{-4, 20, -4},
		{-1, -4, -1}
};

const float_t flt_mean[3][3] =
{
		{0.1111, 0.1111, 0.1111},
		{0.1111, 0.1111, 0.1111},
		{0.1111, 0.1111, 0.1111}
};

mtx_matrixS16_t flt_getLaplacianoMask()
{
	mtx_matrixS16_t mask = mtx_createMatrixS16(3,3);
	int i,j;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			mask.mtx[i][j] = flt_laplacianoMatrix[i][j];

	return mask;
}

mtx_matrixFloat_t flt_getMeanMask()
{
	mtx_matrixFloat_t mask = mtx_createMatrixFloat(3,3);
	int i,j;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			mask.mtx[i][j] = flt_mean[i][j];

	return mask;
}
