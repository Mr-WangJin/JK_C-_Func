#include "jk_file.h"
#include <stdio.h>
#include <stdlib.h>

using namespace JK_NAMESPACE;


bool JK_File::ReadFile(const char* fileName,const char *_Mode, char *&buffer, long &lSize)
{

	FILE *pFile = fopen ( fileName, _Mode );
	if (pFile==NULL) {fputs ("File error",stderr); return false;}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); fclose(pFile); return false;}

	// copy the file into the buffer:
	long result = fread (buffer,1,lSize,pFile);
	fclose (pFile);

	if (result != lSize) {fputs ("Reading error",stderr); free(buffer); buffer = NULL; return false;}
	// terminate
	return true;
}

bool JK_File::WriteFile(const char* fileName, const char *_Mode, const char *buffer, const long &lSize)
{
	FILE *pFile;
	pFile = fopen(fileName, _Mode);
	if (pFile==NULL) {fputs ("File error",stderr); return false;}

	fwrite(buffer, sizeof(char), lSize, pFile);

	fclose(pFile);
	return true;
}