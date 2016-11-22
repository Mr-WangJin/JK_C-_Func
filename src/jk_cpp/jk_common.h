#ifndef _JK_COMMON_H_
#define _JK_COMMON_H_

#include "lib_jk.h"
#include <iostream>

using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a):(b))
#define MAX(a,b) ( (a)>(b) ? (a):(b))

#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }

#define JK_NAMESPACE	JK_CPP
#define BEGIN_JK_NAMESPACE	namespace JK_NAMESPACE {
#define END_JK_NAMESPACE	};
 

#endif