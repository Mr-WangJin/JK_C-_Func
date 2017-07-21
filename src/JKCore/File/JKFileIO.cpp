#include "JKFileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include "JKUtil/JKStringUtil.h"

USING_JK_NAMESPACE


bool JKFileIO::ReadFile(const JKString &fileName, const OpenMode &mode, JKString &data, size_t &lSize)
{
	FILE* pFile;
	errno_t error = fopen_s(&pFile, fileName.c_str(), getMode(mode).c_str());
	if (error != 0) {
		fputs ("File error",stderr);
		return false;
	}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	char* buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) 
	{
		fputs ("Memory error",stderr); 
		fclose(pFile); return false;
	}

	// copy the file into the buffer:
	size_t result = fread (buffer,1,lSize,pFile);
	fclose (pFile);

	data = buffer;
	free(buffer);
	buffer = NULL;
// 	if (result != lSize) {
// 		fputs ("Reading error",stderr); 
// 		free(buffer);
// 		buffer = NULL; 
// 		return false;
// 	}
// 	else {
// 		data = buffer;
// 		free(buffer);
// 		buffer = NULL;
	//}
	return true;
}

bool JKFileIO::WriteFile(const JKString &fileName, const OpenMode &mode, const JKString &data, const size_t &lSize)
{
	FILE *pFile;
	errno_t error = fopen_s(&pFile, fileName.c_str(), getMode(mode).c_str());
	if (error != 0) 
	{
		fputs ("File error",stderr); 
		return false;
	}

	fwrite(data.c_str(), sizeof(char), lSize, pFile);

	fclose(pFile);
	return true;
}

JKString JKFileIO::getMode(const OpenMode & mode)
{
	switch (mode)
	{
	case Read:
		return JKString(_str("r"));
	case Write:
		return JKString(_str("w"));
	case Append:
		return JKString(_str("a"));
	case Read_Plus:
		return JKString(_str("r+"));
	case Write_Plus:
		return JKString(_str("w+"));
	case Append_Plus:
		return JKString(_str("a+"));
	default:
		break;
	}
	return JKString();
}
