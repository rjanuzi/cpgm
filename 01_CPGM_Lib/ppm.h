#ifndef PPM_H_
#define PPM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <matrix.h>

#define ppm_MAGIC_CODE_ASCII		"P3"
#define ppm_MAGIC_CODE_BIN			"P6"
#define ppm_PIXEL_MAX_VALUE			255

/**
 * Estrutura de dados para representar uma
 * imagem PPM no sistema */
typedef struct {
	bool isOk;					/* Diz se a estrutura foi preenchida corretamente. */
	uint8_t maxValue;			/* Valor maximo atribuido a cada pixel. */
	mtx_matrixS16_t imgMatrix;	/* Ponteiro para a matriz da imagem. */
} ppm_img_t;

ppm_img_t ppm_createImg(const char* ppmFilePath);

#endif /* PPM_H_ */
