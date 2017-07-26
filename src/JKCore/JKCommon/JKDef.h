#pragma once

/** ÃüÃû¿Õ¼ä */
#define JK_NAMESPACE	JK_Core
#define USING_JK_NAMESPACE using namespace JK_NAMESPACE;
#define BEGIN_JK_NAMESPACE	namespace JK_NAMESPACE {
#define END_JK_NAMESPACE	};



//½ûÓÃ¿½±´
#define JK_DISABLE_COPY(Class) \
    Class(const Class &)  = delete;\
    Class &operator=(const Class &)  = delete;


#define JK_STRING_LOWER(str) std::transform( str.begin(), str.end(), str.begin(), ::tolower );
#define JK_STRING_UPPER(str) std::transform( str.begin(), str.end(), str.begin(), ::toupper );
