#ifndef _JK_FILE_H_
#define _JK_FILE_H_

#include "Common/JKCommon.h"

BEGIN_JK_NAMESPACE

class JK_API JK_File
{
public:
	/**	
	*	��ȡ�ļ�����buffer��lSize 
	*/
	static bool ReadFile(const char* fileName, const char *_Mode, char *&buffer, size_t &lSize);


	/**	
	*	д���ļ�
	*/
	static bool WriteFile(const char* fileName, const char *_Mode, const char *buffer, const size_t &lSize);

};

END_JK_NAMESPACE



#endif  //_JK_FILE_H_