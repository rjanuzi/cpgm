#include <pgm.h>

pgm_img_t pgm_createImg(const char* pgmFilePath)
{
	int fscanfResultAux, i, j, nLinesTemp, nColsTemp;
	char stringAux[100];
	uint16_t intAux;
	pgm_img_t createdPgmImg;
	FILE* pgmFile;

	createdPgmImg.isOk = false; /* Apenas se torna true se tudo estiver correto ao final. */

	/* Abrindo o arquivo */
	pgmFile = fopen(pgmFilePath, "r");

	if( pgmFile == NULL )
	{
		printf("\npgm_createImg - Erro na abertura da imagem: %s", pgmFilePath);
		return createdPgmImg; /* Termina o programa. */
	}

	/* Lendo o cabecalho */
	fscanfResultAux = fscanf(pgmFile, "%s", stringAux);
	/* A primeira coisa no deve ser a string "P2" (Magic Code) */
	if( fscanfResultAux == 0 || (strcmp(stringAux, PGM_MAGIC_CODE) != 0 ) )
	{
		printf("\npgm_createImg - ERRO: Header PGM invalido.");
		return createdPgmImg;
	}

	/* Pula texto TODO Melhorar esse Skip do comentario. */
	while( fscanf(pgmFile, "%s", stringAux) != EOF  )
	{

		/* O loop para (break) quando encotra uma string que pode ser convertida para um inteiro
		 * no caso de imagens pgm convertidas usando o GIMP eh a versao do filtro. */
		intAux = atoi(stringAux);
		if(intAux != 0)
			break;
	}
	if( fscanfResultAux == EOF )
	{
		printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta.");
		return createdPgmImg;
	}

	/* Recupera numero de cols */
	if((fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		nColsTemp= intAux;
	else
	{
		printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta.");
		return createdPgmImg;
	}

	/* Recupera numero de linhas */
	if((fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		nLinesTemp = intAux;
	else
	{
		printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta.");
		return createdPgmImg;
	}

	/* Recupera numero valor maximo */
	if((fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
		createdPgmImg.maxValue = intAux;
	else
	{
		printf("\npgm_createImg - ERRO: A estrutura do arquivo esta incorreta.");
		return createdPgmImg;
	}

	i = 0;
	j = 0;
	/* Recupera a matriz */
	createdPgmImg.imgMatrix = mtx_createMatrixU8(nLinesTemp, nColsTemp);

	while( (fscanfResultAux = fscanf(pgmFile, "%d", &intAux)) != EOF && fscanfResultAux != 0 )
	{
		createdPgmImg.imgMatrix.mtx[i][j] = intAux;
		j++;
		if( j >= nColsTemp )
		{
			j = 0;
			i++;
		}
	}

	createdPgmImg.isOk = true;

	fclose(pgmFile);

	return createdPgmImg;
}

pgm_img_t pgm_createEmptyImg(int nLines, int nCols)
{
	pgm_img_t newPgmImage;

	newPgmImage.maxValue = PGM_PIXEL_MAX_VALUE;
	newPgmImage.imgMatrix = mtx_createMatrixU8(nLines, nCols);
	if(newPgmImage.imgMatrix.mtx != NULL)
		newPgmImage.isOk = true;
	else
		newPgmImage.isOk = false;

	return newPgmImage;
}

void pgm_destroyPgm(pgm_img_t pgmImgToDestroy)
{
	pgmImgToDestroy.isOk = false;
	pgmImgToDestroy.maxValue = 0;
	mtx_freeMatrixU8(pgmImgToDestroy.imgMatrix);
}

void pgm_savePgmImg(pgm_img_t pgmImgToSave, const char* fileName)
{
	FILE* fileToSave = fopen(fileName, "w");
	int i,j;

	if( fileToSave == NULL )
	{
		printf("\nErro no salvamento da imagem: %s", fileToSave);
		return; /* Termina o programa. */
	}

	fprintf(fileToSave, PGM_MAGIC_CODE);
	fprintf(fileToSave, "\n");
	fprintf(fileToSave, "# Arquivo criado com a biblioteca cpgm Version 1.0\n");
	fprintf(fileToSave, "%d %d\n", pgmImgToSave.imgMatrix.nCols, pgmImgToSave.imgMatrix.nLines);
	fprintf(fileToSave, "%d\n", pgmImgToSave.maxValue);

	for(i = 0; i < pgmImgToSave.imgMatrix.nLines; i++)
		for(j = 0; j < pgmImgToSave.imgMatrix.nCols; j++)
			fprintf(fileToSave, "%d\n", pgmImgToSave.imgMatrix.mtx[i][j]);

	printf("\npgm_savePgmImg  - Nova imagem salva com sucesso no arquivio: %s", fileName);

	fclose(fileToSave);
}

void pgm_sumScalar(pgm_img_t pgmInputImg, int scalarToSum)
{
	mtx_sumScalarU8(pgmInputImg.imgMatrix, scalarToSum);
}

pgm_img_t pgm_diff(pgm_img_t pgmL, pgm_img_t pgmR)
{
	pgm_img_t resultImg;

	resultImg.imgMatrix = mtx_subMatrixU8(pgmL.imgMatrix, pgmR.imgMatrix);
	resultImg.maxValue = PGM_PIXEL_MAX_VALUE;

	if(resultImg.imgMatrix.mtx != NULL)
		resultImg.isOk = true;
	else
		resultImg.isOk = false;

	return resultImg;
}

void pgm_printPgmImgStructure(pgm_img_t dataToPrint)
{
	int i,j;

	printf("\npgm_img_t:\n\tisOk: ");
	printf(dataToPrint.isOk ? "true" : "false");
	printf("\n\tNum colunas: %d\n\tNum linhas: %d\n\tMax value: %d", dataToPrint.imgMatrix.nCols, \
			dataToPrint.imgMatrix.nLines, dataToPrint.maxValue);

	printf("\n\tImg data:");
	mtx_printMatrixU8(dataToPrint.imgMatrix);
}

uint8_t* pgm_createHistogram(pgm_img_t imgToAnalyze)
{
	int i,j;
	uint8_t* histArray = malloc(256);

	if(!imgToAnalyze.isOk)
	{
		printf("\npgm_createHistogram - ERRO imagem invalida.");
		return &histArray[0];
	}

	/* Preenche o array de resultados com 0s */
	for(i = 0; i < 256; i++)
		histArray[i] = 0;

	for(i = 0; i < imgToAnalyze.imgMatrix.nLines; i++)
		for(j = 0; j < imgToAnalyze.imgMatrix.nCols; j++)
			histArray[imgToAnalyze.imgMatrix.mtx[i][j]]++;

	return &histArray[0];
}

void pgm_saveHistogram(const char* fileName, uint8_t* histArray)
{
	FILE* fileToSave = fopen(fileName, "w");
	int i;

	if( fileToSave == NULL )
	{
		printf("\npgm_saveHistogram - Erro no salvamento da imagem: %s", fileToSave);
		return; /* Termina o programa. */
	}

	for(i = 0; i < 256; i++)
		fprintf(fileToSave, "%d\n", histArray[i]);

	printf("\npgm_saveHistogram  - Histograma salvo com sucesso no arquivo: %s", fileName);

	fclose(fileToSave);
}
