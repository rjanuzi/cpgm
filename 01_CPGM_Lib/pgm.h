/**
 * @file pgm.h
 * @author Rafael B. Januzi (rjanuzi@gmail.com)
 * @version 0.1
 *
 * Este arquivo juntamento com o arquivo \ref pgm.c fornece um conjunto de funcoes
 * para manipulacao de imagens manocromaticas na codificacao PGM.
 *
 */

#ifndef _PGM_H_
#define _PGM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <matrix.h>

#define PGM_MAGIC_CODE_ASCII		"P2"
#define PGM_MAGIC_CODE_BIN			"P5"
#define PGM_PIXEL_MAX_VALUE			255
#define PGM_HISTOGRAM_ARRAY_SIZE	256

/**
 * Estrutura de dados para representar uma
 * imagem PGM no sistema */
typedef struct {
	bool isOk;				/* Diz se a estrutura foi preenchida corretamente. */
	uint8_t maxValue;		/* Valor maximo atribuido a cada pixel. */
	mtx_matrixS16_t imgMatrix;	/* Ponteiro para a matriz da imagem. */
} pgm_img_t;

/**
 * Cria uma imagem pgm do tipo \ref pgm_img_t.
 * 
 * @param[in] FILE* pgmFile:
 *	Ponteiro para um arquivo de imagem pgm formatada em ASCII. O ponteiro
 *	jah deve ter sido aberto com sucesso.
 *
 *	Exemplo de header:
 *		P2
 *		# CREATOR: GIMP PNM Filter Version 1.1
 *		<N_COLS> <N_LINES>
 *		<MAX_VALOR_CINZA>
 *		DATA[0][0]
 *		DATA[0][1]
 *		.
 *		.
 *		.
 *		DATA[N_LINES][N_COLS]
 *
 * @return Estrutura \ref pgm_img_t preenchida com os valores lidos do arquivo
 * de imagem pgm. Caso ocorra algum erro na leitura os valores seram corrompidos,
 * isso pode ser verificado pelo campo isOK da estrutura.
 */
pgm_img_t pgm_createImg(const char* pgmFilePath);

/**
 *
 * @param int nLines
 * 	Numero de pixels verticais (height)
 *
 * @param int nCols
 * 	Numero de pixels horizontais (width)
 *
 * @return \ref pgm_img_t
 * 	Estrutura de dados do tipo de imagens PGM instanciada corretamente,
 * 	mas com valores 0s para os pixels.
 *
 */
pgm_img_t pgm_createEmptyImg(int nLines, int nCols);

/**
 * Desaloca toda a memoria dinamicamente alocada para a img.
 *
 * @param pgm_img_t pgmImgToDestroy
 * 	Estrutura de dados para desalocacao de memoria.
 *
 */
void pgm_destroyPgm(pgm_img_t pgmImgToDestroy);

/**
 * Salva um novo arquivo de imagem PGM com as informacoes da estrutura de dados
 * \ref pgm_img_t passsada por parametro.
 *
 * @param pgm_img_t pgmImgToSave
 * 	Estrutura de dados com as informacoes da imagem a ser salva.
 *
 * @param const char* fileName
 * 	String com o nome desejado para o arquivo de saida
 *
 */
void pgm_savePgmImg(pgm_img_t pgmImgToSave, const char* fileName);

/**
 *	Somar um valor escalar a cada pixel da imagem.
 *
 *	@param pgm_img_t pgmInputImg
 *		Imagem a qual sera somado o escalar, a operacao altera a
 *		matriz por referencia.
 *
 *	@param int scalarToSum
 *		Escalar para somar. Valor positivo aumentara o brilho e negativo deminuirah
 *		o brilho.
 */
void pgm_sumScalar(pgm_img_t pgmInputImg, int scalarToSum);

/**
 * Calcula a diferenca de duas imagens pgmL - pgmR
 *
 * Obs.: A diferenca pode ser feita com imagens de tamanhos diferentes,
 * porem as subtracoes seram realizadas apenas em pixels (i,j) onde i,j
 * estao definidos em ambas imagens e a imagem resultante terah tamanho
 * min(iL, iR) x min(jL, jR).
 *
 * @param pgm_img_t pgmL
 * 	Primeira imagem da equacao de diferenca.
 *
 * @param pgm_img_t pgmR
 * 	Segunda imagem da equacao de diferenca.
 *
 * @return \ref pgm_img_t
 * 	Retorna uma nova imagem com o resultado.
 *
 */
pgm_img_t pgm_diff(pgm_img_t pgmL, pgm_img_t pgmR);

/**
 * Calcula aplica a operacao de diff em uma imagem inteira utilizando
 * a mesma mascara, a mascara com a parte da imagem sendo avaliada são
 * comparadas pixel a pixel.
 *
 * @param pgm_img_t pgmImg
 * 	Primeira imagem da equacao de diferenca.
 *
 * @param mtx_matrixS16_t mask
 * 	Mascara que sera subtraida da imagem em blocos.
 *
 * @param uint8_t limiarDeDiferenca
 * 	Define o quanto de diferenca entre cada pixel o algoritmo considera
 * 	a igualdade. Ex.: 50, p1 - p2 > 50, então p1 == p2
 *
 * @return \ref pgm_img_t
 * 	Retorna uma nova imagem com o resultado.
 *
 */
pgm_img_t pgm_findMaskInImagePaP(pgm_img_t pgmImg, mtx_matrixS16_t mask, uint8_t limiarDeDiferenca);

/**
 * Calcula aplica a operacao de diff em uma imagem inteira utilizando
 * a mesma mascara, a mascara com a parte da imagem sendo avaliada são
 * comparadas considerando um valor médio de todos os pixels.
 *
 * @param pgm_img_t pgmImg
 * 	Primeira imagem da equacao de diferenca.
 *
 * @param mtx_matrixS16_t mask
 * 	Mascara que sera subtraida da imagem em blocos.
 *
 * @param uint8_t limiarDeDiferenca
 * 	Define o quanto de diferenca entre cada pixel o algoritmo considera
 * 	a igualdade. Ex.: 50, p1 - p2 > 50, então p1 == p2
 *
 * @return \ref pgm_img_t
 * 	Retorna uma nova imagem com o resultado.
 *
 */
pgm_img_t pgm_findMaskInImageMean(pgm_img_t pgmImg, mtx_matrixS16_t mask, uint8_t limiarDeDiferenca);

/**
 * Calcula aplica a operacao de diff em uma imagem inteira utilizando
 * a mesma mascara, a mascara com a parte da imagem sendo avaliada são
 * comparadas considerando uma porcentagem de pixels iguais. Os pixels
 * sao comparados de acordo com um limiar de diferenca.
 *
 * @param pgm_img_t pgmImg
 * 	Primeira imagem da equacao de diferenca.
 *
 * @param mtx_matrixS16_t mask
 * 	Mascara que sera subtraida da imagem em blocos.
 *
 * @param int equalValorLimiar
 *	Diferenca maxima para considerar pixels iguais.
 *
 * @param uint8_t equalLimiarPercentage
 * 	Define o quanto de porcentagem de similaridade deve existir entre as imagens
 * 	para serem consideradas iguais.
 *
 * @return \ref pgm_img_t
 * 	Retorna uma nova imagem com o resultado.
 *
 */
pgm_img_t pgm_findMaskInImagePercentage(pgm_img_t pgmImg, mtx_matrixS16_t mask, uint8_t equalValorLimiar, float equalLimiarPercentage);

/**
 * Imprime na tela os dados dados de uma imagem PGM, que eh representada no programa
 * pela esrutura \ref pgm_img_t
 *
 * @param \ref pgm_img_t dataToPrint
 *	Estrutura de dados para imprimir.
 */
void pgm_printPgmImgStructure(pgm_img_t dataToPrint);

/**
 * Gera um array de tamanho 256, com os valores referentes ao histograma da imagem.
 * cada posicao do array possui quantas vezes um pixel com o valor do indicie aparece
 * na imagem.
 *
 * @param \ref pgm_img_t imgToAnalyze
 *	Estrutura de da imagem a ser analizada.
 *
 * @return uint8_t*
 * 	Retorna um array do tipo \ref uint8_t com \ref HISTOGRAM_ARRAY_SIZE, onde cada posicao
 * 	tem o numero de vezes que um pixel com o valor do indice existe na imagem.
 */
uint8_t* pgm_createHistogram(pgm_img_t imgToAnalyze);

/**
 * Salva um array com os dados do historgrama que foi gerado com a funcao
 * \ref pgm_createHistogram
 *
 * @param \ref pgm_img_t imgToAnalyze
 *	Estrutura de da imagem a ser analizada.
 */
void pgm_saveHistogram(const char* fileName, uint8_t* histArray);

/**
 * TODO
 */
pgm_img_t pgm_applyMask(pgm_img_t imgToApplyFilter, mtx_matrixS16_t maskToApply, uint8_t threshold);

#endif /* _PGM_H_ */
