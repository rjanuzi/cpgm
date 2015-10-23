/*
 * ffmpeg.c
 *
 *  Created on: Oct 12, 2015
 *      Author: Rafael
 */

#ifndef FFMPEG_C_
#define FFMPEG_C_

#include <ffmpeg.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

void ffmpeg_splitVideoFrames(char* videoPath, char* folderToFramesImgs, float fps)
{
	char cmd[500] = "ffmpeg -i \0";
	char strAux[50];

	strcat(cmd, videoPath);
	strcat(cmd, " -r ");

	sprintf(&strAux[0], "%.2f ", fps);
//	sprintf(&strAux[0], "%.2f -s 576x324 ", fps);
	strcat(cmd, &strAux[0]);

	printf("\n--> %s", folderToFramesImgs);
	strcat(cmd, folderToFramesImgs);
	strcat(cmd, "\\%1d.pgm");

	printf("\ncmd: %s", cmd);

	system(cmd);
}

#endif /* FFMPEG_C_ */
