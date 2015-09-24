#include <stdlib.h>
#include <pgm.h>
#include <jpeg.h>

#define LENA_FILE_NAME			"imgs\\00_lena.pgm"
#define DIFF1_FILE_NAME			"imgs\\01_diff1.pgm"
#define DIFF2_FILE_NAME			"imgs\\02_diff2.pgm"
#define CADEIRA1_FILE_NAME		"imgs\\03_cadeira1.pgm"
#define CADEIRA2_FILE_NAME		"imgs\\04_cadeira2.pgm"
#define BRAIN_FILE_NAME			"imgs\\05_brain.pgm"
#define CARCINOMA_FILE_NAME		"imgs\\06_carcinoma.pgm"
#define CAT_FILE_NAME			"imgs\\07_cat.pgm"
#define CAT_EQUA_FILE_NAME		"imgs\\08_catEqua.pgm"
#define WRIST_FILE_NAME			"imgs\\09_wrist.pgm"

int main(int argc, char** argv)
{
	/* Em C o primeiro parametro argv[0] eh sempre o nome do proprio
	 * programa. */
	/*  TODO - Habilitar para utilizacao de chamada por parametro */
//	char* paramFileName = argv[1];
//
//	if( argc != 2 )
//	{
//		printf("ERRO: Chamada incorreta do programa!\n\tUso correto: %s <originalFileName>\n", argv[0]);
//		return -1;
//	}

	pgm_img_t pgmImage1, pgmImage2, pgmImageResult;

	/* Testando soma por escalar. */
	/*======================================================================*/
	pgmImage1 = pgm_createImg(LENA_FILE_NAME);
	pgm_sumScalar(pgmImage1, 75);
	pgm_savePgmImg(pgmImage1, "imgs\\results\\clareada1.pgm");
	pgm_sumScalar(pgmImage1, 75);
	pgm_savePgmImg(pgmImage1, "imgs\\results\\clareada2.pgm");
	pgm_sumScalar(pgmImage1, -150);
	pgm_savePgmImg(pgmImage1, "imgs\\results\\escurecida1.pgm");
	pgm_sumScalar(pgmImage1, -75);
	pgm_savePgmImg(pgmImage1, "imgs\\results\\escurecida2.pgm");
	pgm_destroyPgm(pgmImage1);
	/*======================================================================*/

	/* Testando diff */
	/*======================================================================*/
	pgmImage1 = pgm_createImg(DIFF1_FILE_NAME);
	pgmImage2 = pgm_createImg(DIFF2_FILE_NAME);
	pgmImageResult = pgm_diff(pgmImage1, pgmImage2);
	pgm_savePgmImg(pgmImageResult, "imgs\\results\\diffResult1.pgm");
	pgm_destroyPgm(pgmImageResult);

	pgmImageResult = pgm_diff(pgmImage2, pgmImage1);
	pgm_savePgmImg(pgmImageResult, "imgs\\results\\diffResult2.pgm");
	pgm_destroyPgm(pgmImageResult);

	pgm_destroyPgm(pgmImage1);
	pgm_destroyPgm(pgmImage2);
	/*======================================================================*/

	/*======================================================================*/

	return 0;
}
