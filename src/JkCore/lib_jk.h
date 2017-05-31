#ifndef _LIB_JK_H_
#define _LIB_JK_H_

#if defined(WIN32) && defined(_JK_BUILD_DLL)
/* We are building jk_cpp as a Win32 DLL */
#define JK_API __declspec(dllexport)
#elif defined(__GNUC__) && defined(_JK_BUILD_DLL)
/* We are building jk_cpp as a shared / dynamic library */
#define JK_API __attribute__((visibility("default")))
#else
/* We are building or calling GLFW as a static library */
#define JK_API
#endif





#endif //_LIB_JK_H_
