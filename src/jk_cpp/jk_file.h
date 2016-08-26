#ifndef _JK_FILE_H_
#define _JK_FILE_H_

#include "lib_jk.h"


namespace jk_cpp
{

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



}



#endif  //_JK_FILE_H_