#ifndef _JK_FILE_H_
#define _JK_FILE_H_

#include "jk_common.h"

BEGIN_JK_NAMESPACE

class JK_API JK_File
{
public:
	/**	
	*	Read File 
	*/
	static bool ReadFile(const char* fileName, const char *_Mode, char *&buffer, long &lSize);


	/**	
	*	Write File
	*/
	static bool WriteFile(const char* fileName, const char *_Mode, const char *buffer, const long &lSize);

};

END_JK_NAMESPACE



#endif  //_JK_FILE_H_