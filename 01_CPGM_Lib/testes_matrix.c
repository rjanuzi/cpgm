#include <testes_matrix.h>

bool tstMtx_testeCreateMatrixS16()
{
	mtx_matrixS16_t m1, m2;
	int i,j, k;

	for(k = 0; k < 50; k++)
	{
		m1 = mtx_createMatrixS16(10000, 10000);
		m2 = mtx_createMatrixS16(10000, 10000);

		for(i = 0; i < m1.nLines; i++)
			for(j = 0; j < m1.nCols; j++)
			{
				m1.mtx[i][j] = i+j;
				m2.mtx[i][j] = i+j;
			}

		for(i = 0; i < m1.nLines; i++)
			for(j = 0; j < m1.nCols; j++)
				if( m1.mtx[i][j] != m2.mtx[i][j])
					return false;

		mtx_freeMatrixS16(m1);
		mtx_freeMatrixS16(m2);

		printf("\nExecutando teste tstMtx_testeCreateS16... %.2f%c", ((((float)k)/50.0)*100.0), '%');
	}

	return true;
}

bool tstMtx_testeCreateMatrixFloat()
{
	mtx_matrixFloat_t m1, m2;
	int i,j, k;

	for(k = 0; k < 50; k++)
	{
		m1 = mtx_createMatrixFloat(10000, 10000);
		m2 = mtx_createMatrixFloat(10000, 10000);

		for(i = 0; i < m1.nLines; i++)
			for(j = 0; j < m1.nCols; j++)
			{
				m1.mtx[i][j] = i+j;
				m2.mtx[i][j] = i+j;
			}

		for(i = 0; i < m1.nLines; i++)
			for(j = 0; j < m1.nCols; j++)
				if( m1.mtx[i][j] != m2.mtx[i][j])
					return false;

		mtx_freeMatrixFloat(m1);
		mtx_freeMatrixFloat(m2);

		printf("\nExecutando teste tstMtx_testeCreateFloat... %.2f%c", ((((float)k)/50.0)*100.0), '%');
	}

	return true;
}

bool tstMtx_testeCreateArray16()
{
	mtx_arrayS16_t a1, a2;
	int i, k;

	for(k = 0; k < 50; k++)
	{
		a1 = mtx_createArrayS16(100000);
		a2 = mtx_createArrayS16(100000);

		for(i = 0; i < a1.size; i++)
		{
			a1.array[i] = i;
			a2.array[i] = i;
		}

		for(i = 0; i < a1.size; i++)
			if(a1.array[i] != a1.array[i])
				return false;

		mtx_freeArrayS16(a1);
		mtx_freeArrayS16(a2);

		printf("\nExecutando teste tstMtx_testeCreateArray16... %.2f%c", ((((float)k)/50.0)*100.0), '%');
	}

	return true;
}

bool tstMtx_testeCreateArrayFloat()
{
	mtx_arrayFloat_t a1, a2;
	int i, k;

	for(k = 0; k < 50; k++)
	{
		a1 = mtx_createArrayFloat(100000);
		a2 = mtx_createArrayFloat(100000);

		for(i = 0; i < a1.size; i++)
		{
			a1.array[i] = (i+30)/(i+25);
			a2.array[i] = (i+30)/(i+25);
		}

		for(i = 0; i < a1.size; i++)
			if(a1.array[i] != a1.array[i])
				return false;

		mtx_freeArrayFloat(a1);
		mtx_freeArrayFloat(a2);

		printf("\nExecutando teste tstMtx_testeCreateArrayFloat... %.2f%c", ((((float)k)/50.0)*100.0), '%');
	}

	return true;
}

bool tstMtx_testeAddToBack()
{
	mtx_arrayFloat_t a1, newValues, newA1, expectedA;
	bool result;

	a1 = mtx_createArrayFloat(3);
	newValues = mtx_createArrayFloat(4);
	expectedA = mtx_createArrayFloat(7);

	a1.array[0] = 3.5;
	a1.array[1] = -2.125;
	a1.array[2] = 71824.2516;

	newValues.array[0] = -12.24;
	newValues.array[1] = 1256.2;
	newValues.array[2] = 123.52;
	newValues.array[3] = 4.0;

	expectedA.array[0] = 3.5;
	expectedA.array[1] = -2.125;
	expectedA.array[2] = 71824.2516;
	expectedA.array[3] = -12.24;
	expectedA.array[4] = 1256.2;
	expectedA.array[5] = 123.52;
	expectedA.array[6] = 4.0;

	newA1 = mtx_addToBack(a1, newValues);

	result = mtx_equalsArrayFloat(newA1, expectedA);

	mtx_freeArrayFloat(a1);
	mtx_freeArrayFloat(newValues);
	mtx_freeArrayFloat(newA1);
	mtx_freeArrayFloat(expectedA);

	return result;
}
