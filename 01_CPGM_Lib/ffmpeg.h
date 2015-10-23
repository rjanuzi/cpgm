/*
 * ffmpeg.h
 *
 *  Created on: Oct 12, 2015
 *      Author: Rafael B. Januzi
 */

#ifndef FFMPEG_H_
#define FFMPEG_H_

#include <string.h>

/**
 *	Separa todos os frames de um video utilizando o programa ffmpeg
 *
 *	@param \ref char* videoPath
 *		Caminho completo do video de entrada.
 *	@param \ref float fps
 *		Frames por segundo (FPS) que do segundo.
 *	@param \ref char* folderToFramesImgs
 *		Path completo ateh o folder onde os frames deve ser armazenados.
 *
 */
void ffmpeg_splitVideoFrames(char* videoPath, char* folderToFramesImgs, float fps);

#endif /* FFMPEG_H_ */
