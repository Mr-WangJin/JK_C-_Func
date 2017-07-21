#ifndef _JK_FILE_H_
#define _JK_FILE_H_

#include "Common/JKCommon.h"
#include "Common/JKBase.h"

BEGIN_JK_NAMESPACE

class JK_API JKFileIO : public JKBase
{
public:
	enum OpenMode
	{
		Read,			//only read
		Write,			//only write
		Append,			//append
		Read_Plus,		//read write
		Write_Plus,		//new file and write 
		Append_Plus		//
	};
public:
	/**	
	*	读取文件返回buffer和lSize 
	*/
	static bool ReadFile(const JKString &fileName, const OpenMode &mode,  JKString &data, size_t &lSize) ;


	/**	
	*	写入文件
	*/
	static bool WriteFile(const JKString &fileName, const OpenMode &mode, const JKString &data, const size_t &lSize);

private:
	static JKString getMode(const OpenMode &mode);

};

END_JK_NAMESPACE



#endif  //_JK_FILE_H_