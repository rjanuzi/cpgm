/*
 * videoBuffer.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Rafael B. Januzi
 */

#ifndef VIDEOBUFFER_H_
#define VIDEOBUFFER_H_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <pgm.h>

/**
 * TODO
 */
void vb_initVideoBuffer(char* framesFolder, char* framesNamePrefix);

/**
 * Verifica se existem mais frames para serem obtidos.
 *
 *	@return \ref bool
 *		True se existem mais frames e False se nao existem mais frames.
 */
bool vb_hasMoreFrames();

/**
 * TODO
 */
pgm_img_t vb_getNextFrameImg();

#endif /* VIDEOBUFFER_H_ */
