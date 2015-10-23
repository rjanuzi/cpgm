/*
 * videoBuffer.c
 *
 *  Created on: Oct 12, 2015
 *      Author: Rafael B. Januzi
 */

#include <videoBuffer.h>

static int vb_currentFrame = -1;
char vb_framesNamePath[500];

void vb_initVideoBuffer(char* framesFolder, char* framesNamePrefix)
{
	int  i;

	for(i = 0; i < 500; i++)
		vb_framesNamePath[i] = '\0';

	strcat(vb_framesNamePath, framesFolder);
	strcat(vb_framesNamePath, "\\");
	strcat(vb_framesNamePath, framesNamePrefix);
	vb_currentFrame = 1;
}

bool vb_hasMoreFrames()
{
	FILE* currentFrameFile;
	char currentFramePath[500];
	char strAux[50];
	int i;

	for(i = 0; i < 500; i++)
		currentFramePath[i] = vb_framesNamePath[i];

	if(vb_currentFrame < 0)
	{
		printf("\nERRO - vb_getNextFrameImg: videoBuffer nao inicializada!");
		return false;
	}

	sprintf(strAux, "%d.pgm", (vb_currentFrame+1));
	strcat(currentFramePath, strAux);

	currentFrameFile = fopen(currentFramePath, "r");

	if(currentFrameFile != NULL)
	{
		fclose(currentFrameFile);
		return true;
	}
	return false;
}

pgm_img_t vb_getNextFrameImg()
{
	pgm_img_t frameImg;
	char currentFramePath[500];
	char strAux[50];

	if(vb_currentFrame < 0)
	{
		printf("\nERRO - vb_getNextFrameImg: videoBuffer nao inicializada ou nao existem mais frames!");
		return frameImg;
	}

	strcpy(currentFramePath, vb_framesNamePath);
	sprintf(strAux, "%d.pgm", vb_currentFrame++); /* Jah aponta para o proximo frame. */
	strcat(currentFramePath, strAux);

	frameImg = pgm_createImg(currentFramePath);

	return frameImg;
}

