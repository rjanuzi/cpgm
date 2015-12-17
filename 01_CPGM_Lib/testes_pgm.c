#include <testes_pgm.h>

bool tstPgm_testeCreateImg1()
{
	pgm_img_t img1, img2;
	int i;

	printf("\nExecutando teste tstPgm_testeCreateImg1....");

	/* Imagem em ASCII */
	for(i = 0; i < 10; i++)
	{
		img1 = pgm_createImg(LENA_GRANDE_FILE_NAME);
		img2 = pgm_createImg(LENA_GRANDE_FILE_NAME);

		if(pgm_equals(img1, img2) == false)
		{
			printf("\nFALHOU - tstPgm_testeCreateImg1: Iteracao: %d\n %s != %s", i, LENA_GRANDE_FILE_NAME, LENA_GRANDE_FILE_NAME);
			pgm_destroyPgm(img1);
			pgm_destroyPgm(img2);
			return false;
		}

		pgm_destroyPgm(img1);
		pgm_destroyPgm(img2);

		printf(" %.2f%s", (( ((float)i)/20.0)*100.0), "%");
	}

	/* Imagem em binario. */
	for(i = 0; i < 10; i++)
	{
		img1 = pgm_createImg(LENA_GRANDE_FILE_NAME);
		img2 = pgm_createImg(LENA_GRANDE_BIN_FILE_NAME);

		pgm_savePgmImg(img1, "teste1.pgm");
		pgm_savePgmImg(img2, "teste2.pgm");

		if(pgm_equals(img1, img2) == false)
		{
			printf("\nFALHOU - tstPgm_testeCreateImg1: Iteracao: %d\n %s != %s", i, LENA_GRANDE_FILE_NAME, LENA_GRANDE_BIN_FILE_NAME);
			pgm_destroyPgm(img1);
			pgm_destroyPgm(img2);
			return false;
		}

		pgm_destroyPgm(img1);
		pgm_destroyPgm(img2);

		printf(" %.2f%s", (( ((float)(i+10))/20.0)*100.0), "%");
	}

	return true;
}

bool tstPgm_testeSaveImg1()
{
	pgm_img_t img1, img2;
	int i;

	printf("\nExecutando teste tstPgm_testeSaveImg1....");

	for(i = 0; i < 10; i++)
	{
		img1 = pgm_createImg(LENA_GRANDE_FILE_NAME);
		pgm_savePgmImg(img1, "imgs\\testsResults\\lenaGrandeCpy.pgm");
		img2 = pgm_createImg("imgs\\testsResults\\lenaGrandeCpy.pgm");

		if(pgm_equals(img1, img2) == false)
		{
			printf("\nFALHOU - tstPgm_testeSaveImg1: Iteracao: %d\n %s != imgs\\testsResults\\lenaCpy.pgm", i, LENA_GRANDE_FILE_NAME);
			pgm_destroyPgm(img1);
			pgm_destroyPgm(img2);
			return false;
		}

		pgm_destroyPgm(img1);
		pgm_destroyPgm(img2);

		printf(" %.2f%s", (( ((float)i)/10.0)*100.0), "%");
	}

	for(i = 0; i < 10; i++)
	{
		img1 = pgm_createImg(LENA_GRANDE_BIN_FILE_NAME);
		pgm_savePgmImg(img1, "imgs\\testsResults\\lenaGrandeBinCpy.pgm");
		img2 = pgm_createImg("imgs\\testsResults\\lenaGrandeBinCpy.pgm");

		if(pgm_equals(img1, img2) == false)
		{
			printf("\nFALHOU - tstPgm_testeSaveImg1: Iteracao: %d\n %s != imgs\\testsResults\\lenaCpy.pgm", i, LENA_GRANDE_FILE_NAME);
			pgm_destroyPgm(img1);
			pgm_destroyPgm(img2);
			return false;
		}

		pgm_destroyPgm(img1);
		pgm_destroyPgm(img2);

		printf(" %.2f%s", (( ((float)(i+10))/20.0)*100.0), "%");
	}

	return true;
}

bool tstPgm_testeFramesVideo()
{
	uint16_t i, lastFrame = 1420; /* Depende do video. */
	char strAux[100], frameNameAux[100], path1Aux[100] = FRAMES_FOLDER_1, path2Aux[100] = FRAMES_FOLDER_2;
	pgm_img_t img1, img2;

	printf("\nExecutando teste tstPgm_testeFramesVideo....");

	ffmpeg_splitVideoFrames(VIDEO_pedestreEsq, FRAMES_FOLDER_1, 30.0);
	ffmpeg_splitVideoFrames(VIDEO_pedestreEsq, FRAMES_FOLDER_2, 30.0);

	for(i = 1; i <= lastFrame; i++)
	{
		strcpy(frameNameAux,path1Aux);
		sprintf(strAux, "%d.pgm", i);
		strcat(frameNameAux, strAux);
		img1 = pgm_createImg(frameNameAux);

		strcpy(frameNameAux,path2Aux);
		sprintf(strAux, "%d.pgm", i);
		strcat(frameNameAux, strAux);
		img2 = pgm_createImg(frameNameAux);

		if(img1.isOk == false || img1.isOk == false)
		{
			printf("\nERRO - tstPgm_testeFramesVideo: Imagens nao criadas com sucesso.");
			return 0;
		}

		if(pgm_equals(img1, img2) == false)
		{
			printf("\nImagens diferentes: %d", i);
			pgm_destroyPgm(img1);
			pgm_destroyPgm(img2);
		}

		pgm_destroyPgm(img1);
		pgm_destroyPgm(img2);

		printf(" %.2f%s", (( ((float)i)/lastFrame)*100), "%");
	}
	return true;
}

bool tstPgm_testeMediaMask()
{
	pgm_img_t pgmImage1, pgmImage2, pgmImageResult;
	mtx_matrixFloat_t mask;

	pgmImage1 = pgm_createImg(LENA_GRANDE_FILE_NAME);
	mask = flt_getMeanMask();

	pgmImageResult = pgm_applyMaskFloat(pgmImage1, mask);

	pgm_savePgmImg(pgmImageResult, "imgs\\testsResults\\lenaMedia.pgm");

	pgmImage2 = pgm_createImg("imgs\\testsResults\\lenaMedia.pgm");

	if(pgm_equals(pgmImage2, pgmImageResult) == false)
	{
		pgm_destroyPgm(pgmImageResult);
		pgm_destroyPgm(pgmImage1);
		pgm_destroyPgm(pgmImage2);
		return false;
	}

	pgm_destroyPgm(pgmImageResult);
	pgm_destroyPgm(pgmImage1);
	pgm_destroyPgm(pgmImage2);

	return true;
}

bool tstPgm_testeMediaMask2()
{
	pgm_img_t pgmImage1, pgmImage2, pgmImageResult;
	mtx_matrixFloat_t mask;

	printf("\nCarregando imagem...");
	pgmImage1 = pgm_createImg("C:\\imgs\\mapa1_ascii.pgm");
	mask = flt_getMeanMask();

	pgmImageResult = pgm_applyMaskFloat(pgmImage1, mask);

	printf("\nSalvando resultado...");
	pgm_savePgmImg(pgmImageResult, "C:\\imgs\\mapa1_ascii_result.pgm");

	return true;
}

bool tstPgm_testeCreateCoocorrenciaMtx()
{
	pgm_img_t img;
	mtx_matrixFloat_t coocorrenciaMtx;

	img = pgm_createImg(CARCINOMA_FILE_NAME);

	coocorrenciaMtx = pgm_createCoocorrenciaMtx(img, _0_GRAUS, 1);

	pgm_destroyPgm(img);

	return true;
}
