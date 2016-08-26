#ifndef _JK_COMMON_H_
#define _JK_COMMON_H_


#define MIN(a,b) ( (a)<(b) ? (a):(b))
#define MAX(a,b) ( (a)>(b) ? (a):(b))

#define AUTO_DELETE(ptr) {if(ptr){delete ptr;(ptr)=NULL;} }


#endif