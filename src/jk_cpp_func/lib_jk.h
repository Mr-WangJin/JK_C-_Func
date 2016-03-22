#ifndef _LIB_JK_H_
#define _LIB_JK_H_

#if defined(WIN32) && defined(_JK_BUILD_DLL)
/* We are building JK_CPP_FUNC as a Win32 DLL */
#define JKAPI __declspec(dllexport)
#elif defined(__GNUC__) && defined(_JK_BUILD_DLL)
/* We are building JK_CPP_FUNC as a shared / dynamic library */
#define JKAPI __attribute__((visibility("default")))
#else
/* We are building or calling GLFW as a static library */
#define JKAPI
#endif





#endif //_LIB_JK_H_
