#ifndef _JK_COMMON_H_
#define _JK_COMMON_H_

#include "lib_jk.h"
#include <string>
#include <assert.h>
#include <vector>
#include "JKDef.h"


using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a):(b))
#define MAX(a,b) ( (a)>(b) ? (a):(b))



#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }


/** 定义字符串类型 */
#ifdef _UNICODE
typedef std::wstring JKString;
typedef wchar_t* pstr;
typedef const wchar_t* cpstr;
#define _str(x) L##x

#else
typedef std::string JKString;
typedef char* PStr;
typedef const char* CPStr;
#define _str(x) x

#endif // _UNICODE

/** 定义基本数据类型 */
typedef unsigned long long JKUInt64;
typedef unsigned int JKUInt;
typedef unsigned long JKULong;
typedef unsigned long JKLong;
typedef unsigned short JKUShort;





#endif