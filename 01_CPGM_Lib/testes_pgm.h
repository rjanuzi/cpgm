#ifndef TESTES_PGM_H_
#define TESTES_PG_H_

#include <pgm.h>
#include <ffmpeg.h>
#include <stdbool.h>
#include <filters.h>

#define LENA_FILE_NAME				"imgs\\00_lena.pgm"
#define LENA_BIN_FILE_NAME			"imgs\\00_lenaBin.pgm"
#define LENA_GRANDE_FILE_NAME		"imgs\\00_lena_grande.pgm"
#define LENA_GRANDE_BIN_FILE_NAME	"imgs\\00_lena_grande_bin.pgm"
#define DIFF1_FILE_NAME				"imgs\\01_diff1.pgm"
#define DIFF2_FILE_NAME				"imgs\\02_diff2.pgm"
#define CADEIRA1_FILE_NAME			"imgs\\03_cadeira1.pgm"
#define CADEIRA2_FILE_NAME			"imgs\\04_cadeira2.pgm"
#define BRAIN_FILE_NAME				"imgs\\05_brain.pgm"
#define CARCINOMA_FILE_NAME			"imgs\\06_carcinoma.pgm"
#define CAT_FILE_NAME				"imgs\\07_cat.pgm"
#define CAT_EQUA_FILE_NAME			"imgs\\08_catEqua.pgm"
#define WRIST_FILE_NAME				"imgs\\09_wrist.pgm"
#define DCT_ORIGNIAL_FILE_NAME		"imgs\\10_DctOriginal.pgm"
#define WALLY_FILE_NAME				"imgs\\11_wally.pgm"
#define MAPA_WALLY_FILE_NAME		"imgs\\12_mapa_wally.pgm"
#define WALLY_PEQUENO_FILE_NAME		"imgs\\13_wally_pequeno_cinza.pgm"
#define MAPA_WALLY_2_FILE_NAME		"imgs\\14_mapa_matriz_cinza.pgm"
#define IMG_PARA_SEGMENTACAO		"imgs\\18_img_para_segmentacao.pgm"
#define IMG_PARA_SEGMENTACAO_BIN	"imgs\\18_img_para_segmentacaoBIN.pgm"

#define VIDEO_carroEsq				"C:\\Videos_PI\\01_carro_esq.MOV"
#define VIDEO_carroEsq2				"C:\\Videos_PI\\02_carro_esq2.MOV"
#define VIDEO_pedestreEsq			"C:\\Videos_PI\\03_pedestre_dir.MOV"
#define VIDEO_bolaDirLenta			"C:\\Videos_PI\\04_bola_dir_lenta.mp4"
#define VIDEO_bolaCima				"C:\\Videos_PI\\05_bola_cima.MOV"
#define VIDEO_bolaDir				"C:\\Videos_PI\\06_bola_dir.MOV"
#define VIDEO_semMovimento			"C:\\Videos_PI\\07_sem_movimento.MOV"
#define VIDEO_bolaEsq				"C:\\Videos_PI\\08_bola_esq.mp4"
#define FRAMES_PREFIX				""
#define FRAMES_FOLDER_1				"frames1\\"
#define FRAMES_FOLDER_2				"frames2\\"
#define IMG_TESTS_RESULTS_FOLDER	"imgs\\testsResults\\"

bool tstPgm_testeCreateImg1();
bool tstPgm_testeSaveImg1();
bool tstPgm_testeFramesVideo();
bool tstPgm_testeMediaMask();
bool tstPgm_testeMediaMask2();
bool tstPgm_testeCreateCoocorrenciaMtx();

#endif /* TESTES_PGM_H_ */
