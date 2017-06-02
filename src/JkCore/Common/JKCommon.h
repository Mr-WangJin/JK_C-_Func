#ifndef _JK_COMMON_H_
#define _JK_COMMON_H_

#include "lib_jk.h"
#include <string>

using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a):(b))
#define MAX(a,b) ( (a)>(b) ? (a):(b))



#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }



/** ÃüÃû¿Õ¼ä */
#define JK_NAMESPACE	JK_Core
#define BEGIN_JK_NAMESPACE	namespace JK_NAMESPACE {
#define END_JK_NAMESPACE	};


//½ûÓÃ¿½±´
#define JK_DISABLE_COPY(Class) \
    Class(const Class &)  = delete;\
    Class &operator=(const Class &)  = delete;

#ifdef _UNICODE
typedef std::wstring JKString;
typedef wchar_t* pstr;
typedef const wchar_t* cpstr;
#define _gstr(x) L##x

#define JK_STRING_LOWER(str) std::transform( str.begin(), str.end(), str.begin(), ::towlower );
#define JK_STRING_UPPER(str) std::transform( str.begin(), str.end(), str.begin(), ::towupper );

#else
typedef std::string JKString;
typedef char* PStr;
typedef const char* CPStr;
#define _gstr(x) x

#define JK_STRING_LOWER(str) std::transform( str.begin(), str.end(), str.begin(), ::tolower );
#define JK_STRING_UPPER(str) std::transform( str.begin(), str.end(), str.begin(), ::toupper );

#endif // _UNICODE
 

#endif