#ifndef _JK_COMMON_H_
#define _JK_COMMON_H_

#include "lib_jk.h"
#include <string>
#include <assert.h>
#include <vector>
#include "JKDef.h"


using namespace std;

BEGIN_JK_NAMESPACE

#define MIN(a,b) ( (a)<(b) ? (a):(b))
#define MAX(a,b) ( (a)>(b) ? (a):(b))



#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }


/** �����ַ������� */
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

/** ��������������� */
typedef int						JKInt;
typedef unsigned int			JKUInt;
typedef long long				JKInt64;
typedef unsigned long long		JKUInt64;
typedef long					JKLong;
typedef unsigned long			JKULong;
typedef short					JKShort;
typedef unsigned short			JKUShort;
typedef float					JKFloat;
typedef double					JKDouble;
typedef char					JKChar;




END_JK_NAMESPACE

#endif