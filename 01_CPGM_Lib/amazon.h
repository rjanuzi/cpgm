#ifndef AMAZON_H_
#define AMAZON_H_

#include <pgm.h>
#include <filters.h>
#include <math.h>

pgm_img_t amz_applyMediaNTimes(char* inputImgPath, int times);

pgm_img_t amz_applyMaxNTimes(char* inputImgPath, int times);

pgm_img_t amz_preProcessImg(char* inputImgPath, int masksCount);

pgm_img_t amz_blackForestRegions(pgm_img_t inputImg, int limiar);

pgm_img_t amz_blackForestRegions2(pgm_img_t inputImg, int limiar, int blockSize);

//double log2( double n );

#endif /* AMAZON_H_ */
