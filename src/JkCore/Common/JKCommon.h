#ifndef _JK_COMMON_H_
#define _JK_COMMON_H_

#include "lib_jk.h"

using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a):(b))
#define MAX(a,b) ( (a)>(b) ? (a):(b))



#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }




#define JK_NAMESPACE	JK_Core
#define BEGIN_JK_NAMESPACE	namespace JK_NAMESPACE {
#define END_JK_NAMESPACE	};


//½ûÓÃ¿½±´
#define JK_DISABLE_COPY(Class) \
    Class(const Class &)  = delete;\
    Class &operator=(const Class &)  = delete;
 

#endif