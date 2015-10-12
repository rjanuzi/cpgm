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

mtx_matrixS16_t flt_getLaplacianoMask()
{
	mtx_matrixS16_t mask = mtx_createMatrixS16(3,3);
	int i,j;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			mask.mtx[i][j] = flt_laplacianoMatrix[i][j];

	return mask;
}
