#ifndef _JK_COMMON_H_
#define _JK_COMMON_H_

#include "lib_jk.h"
#include <string>
#include <assert.h>
#include <vector>


using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a):(b))
#define MAX(a,b) ( (a)>(b) ? (a):(b))



#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }



/** �����ռ� */
#define JK_NAMESPACE	JK_Core
#define BEGIN_JK_NAMESPACE	namespace JK_NAMESPACE {
#define END_JK_NAMESPACE	};


//���ÿ���
#define JK_DISABLE_COPY(Class) \
    Class(const Class &)  = delete;\
    Class &operator=(const Class &)  = delete;

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
 


#define JK_STRING_LOWER(str) std::transform( str.begin(), str.end(), str.begin(), ::tolower );
#define JK_STRING_UPPER(str) std::transform( str.begin(), str.end(), str.begin(), ::toupper );

#endif