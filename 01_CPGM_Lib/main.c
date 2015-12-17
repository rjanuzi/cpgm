#include <stdlib.h>
#include <pgm.h>
#include <jpeg.h>
#include <filters.h>
#include <ffmpeg.h>
#include <videoBuffer.h>
#include <amazon.h>

#include <testes_matrix.h>

int main(int argc, char** argv)
{
	/* Em C o primeiro parametro argv[0] eh sempre o nome do proprio
	 * programa. */
	/*  TODO - Habilitar para utilizacao de chamada por parametro */
	char* paramFileName = argv[1];

	if( argc != 2 )
	{
		printf("ERRO: Chamada incorreta do programa!\n\tUso correto: %s <originalFileName>\n", argv[0]);
		return -1;
	}

	//	pgm_img_t pgmImage1, pgmImage2, pgmImageResult;
	//
	/* Testando soma por escalar. */
	/*======================================================================*/
	//		pgmImage1 = pgm_createImg(LENA_FILE_NAME);
	//		pgm_sumScalar(pgmImage1, 75);
	//		pgm_savePgmImg(pgmImage1, "imgs\\results\\lenaClareada1.pgm");
	//		pgm_sumScalar(pgmImage1, 75);
	//		pgm_savePgmImg(pgmImage1, "imgs\\results\\lenaClareada2.pgm");
	//		pgm_sumScalar(pgmImage1, -150);
	//		pgm_savePgmImg(pgmImage1, "imgs\\results\\lenaEscurecida1.pgm");
	//		pgm_sumScalar(pgmImage1, -75);
	//		pgm_savePgmImg(pgmImage1, "imgs\\results\\lenaEscurecida2.pgm");
	//		pgm_destroyPgm(pgmImage1);
	//	/*======================================================================*/
	//
	//	/* Testando diff */
	//	/*======================================================================*/
	//		pgmImage1 = pgm_createImg(DIFF1_FILE_NAME);
	//		pgmImage2 = pgm_createImg(DIFF2_FILE_NAME);
	//		pgmImageResult = pgm_diff(pgmImage1, pgmImage2);
	//		pgm_savePgmImg(pgmImageResult, "imgs\\results\\diffResult1.pgm");
	//		pgm_destroyPgm(pgmImageResult);
	//
	//		pgmImageResult = pgm_diff(pgmImage2, pgmImage1);
	//		pgm_savePgmImg(pgmImageResult, "imgs\\results\\diffResult2.pgm");
	//		pgm_destroyPgm(pgmImageResult);
	//
	//		pgm_destroyPgm(pgmImage1);
	//		pgm_destroyPgm(pgmImage2);
	//	/*======================================================================*/
	//
	//	/* Testando PGM binaria */
	//	/*======================================================================*/
	//	pgmImage1 = pgm_createImg(MAPA_WALLY_2_FILE_NAME);
	//	pgm_sumScalar(pgmImage1, 75);
	//	pgm_savePgmImg(pgmImage1, "imgs\\results\\mapaWally2Clareada1.pgm");
	//	pgm_sumScalar(pgmImage1, -150);
	//	pgm_savePgmImg(pgmImage1, "imgs\\results\\mapaWally2Escurecida1.pgm");
	//
	//	/* Testando aplicacao de mascaras (laplaciano) */
	//	/*======================================================================*/
	//	pgmImage1 = pgm_createImg(IMG_PARA_SEGMENTACAO);
	//	mtx_matrixS16_t mask = flt_getLaplacianoMask();
	//	pgmImageResult = pgm_applyMaskS16(pgmImage1, mask, 0);
	//	pgm_savePgmImg(pgmImageResult, "imgs\\results\\laplacianoTest.pgm");
	//	/*======================================================================*/

	/* Calculando velocidade de um objeto no video. */
	/*======================================================================*/
	//	ffmpeg_splitVideoFrames(VIDEO_DIR_ESQ, 30.0, FRAMES_FOLDER_1);
	//	vb_initVideoBuffer(FRAMES_FOLDER_1, FRAMES_PREFIX);
	//
	//	int i, j, count = 1;
	//	char aux[300];
	//	mtx_pos primeirasPosicoesVistas[1000];
	//
	//	pgmImage1 = vb_getNextFrameImg();
	//	while(vb_hasMoreFrames())
	//	{
	//		pgmImage2 = vb_getNextFrameImg();
	//		pgmImageResult = pgm_diffLim(pgmImage1, pgmImage2, 30);
	//		sprintf(aux, "videos\\frames2\\%d.pgm", count++);
	//		pgm_savePgmImg(pgmImageResult, aux);
	//
	//		/* Armazena todas as primeiras posicoes com mudanca. */
	//		for(i = 0; i < 1000; i++)
	//		{
	//			primeirasPosicoesVistas[count-1].lineIndex = 0;
	//			primeirasPosicoesVistas[count-1].colIndex = 0;
	//		}
	//		for(i = 0; i < pgmImageResult.imgMatrix.nLines; i++)
	//			for(j = 0; j < pgmImageResult.imgMatrix.nCols; j++)
	//				if(pgmImageResult.imgMatrix.mtx[i][j] == 255)
	//				{
	//					primeirasPosicoesVistas[count-1].lineIndex = i;
	//					primeirasPosicoesVistas[count-1].colIndex = j;
	//					break;
	//				}
	//
	////		pgmImage1 = pgmImage2;
	//		pgm_destroyPgm(pgmImage2);
	//		pgm_destroyPgm(pgmImageResult);
	//	};
	//
	//	pgm_destroyPgm(pgmImage1);
	//
	//	/* Calcula quantos pixels variou em cada eixo a cada 30 frames. */
	//	int aux1, aux2;
	//	for(i = 0; i < 999; i++)
	//	{
	//		aux1 = primeirasPosicoesVistas[i].lineIndex-primeirasPosicoesVistas[i+1].lineIndex;
	//		aux2 = primeirasPosicoesVistas[i].colIndex-primeirasPosicoesVistas[i+1].colIndex;
	//
	//		if( aux1 < -30)
	//			aux1 = 0;
	//		else
	//			if(aux1 > 30)
	//				aux1 = 0;
	//
	//		if( aux2 < -30)
	//			aux2 = 0;
	//		else
	//			if(aux2 > 30)
	//				aux2 = 0;
	//
	//		if(aux1 != 0 || aux2 != 0)
	//			printf("\n Velocidade no eixos x e y em pixel/frame: (%d, %d)", aux1, aux2);
	//	}
	//
	/*======================================================================*/


	/* Execucao de testes */
	/*======================================================================*/
	//	printf("\nResult: %d", tstMtx_testeCreateMatrixS16());
	//	printf("\nResult: %d", tstMtx_testeCreateMatrixFloat());
	//	printf("\nResult: %d", tstMtx_testeCreateArray16());
	//	printf("\nResult: %d", tstMtx_testeCreateArrayFloat());
	//	printf("\nResult: %d", tstMtx_testeAddToBack());
	//	printf("\nResult: %d", tstPgm_testeCreateCoocorrenciaMtx());
	//	printf("\nResult: %d", tstPgm_testeCreateImg1());
	//	printf("\nResult: %d", tstPgm_testeSaveImg1());
	//	printf("\nResult: %d", tstPgm_testeFramesVideo());
	// 	printf("\nResult: %d", tstPgm_testeMediaMask());
	//	printf("\nResult: %d", tstPgm_testeMediaMask2());

	/*======================================================================*/

	/* Trabalho final (Primeira tentativa, utilizando médias e max com limiar) */
	/*======================================================================*/
//	pgm_img_t preProcessedImg, resultImg;
//
//	preProcessedImg = amz_preProcessImg(paramFileName, 4);
////	preProcessedImg = pgm_createImg(paramFileName);
//	resultImg = amz_blackForestRegions(preProcessedImg, 10);
//
//	pgm_destroyPgm(preProcessedImg);
//	pgm_savePgmImg(resultImg, "C:\\Users\\Rafael\\Desktop\\result.pgm");
//
//	system("start /b C:\\Users\\Rafael\\Desktop\\result.pgm");

	/*======================================================================*/

	/* Trabalho final (Sgunda tentativa, Entropia em subimagens.) */
	/*======================================================================*/
	pgm_img_t preProcessedImg, resultImg;
	uint32_t* histo;

	preProcessedImg = pgm_createImg(paramFileName);
	histo = pgm_createHistogram(preProcessedImg);
	pgm_saveHistogram("testeHisto", histo);
//	resultImg = amz_blackForestRegions2(preProcessedImg, 20, 200);

//	pgm_destroyPgm(preProcessedImg);
//	pgm_savePgmImg(resultImg, "C:\\Users\\Rafael\\Desktop\\result.pgm");
//	pgm_destroyPgm(resultImg);

	system("start /b C:\\Users\\Rafael\\Desktop\\result.pgm");

	/*======================================================================*/

	return 0;
}
