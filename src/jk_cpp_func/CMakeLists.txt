
SET(PROJECT_NAME "JK_CPP_FUNC")

ADD_DEFINITIONS(-D_JK_BUILD_DLL)

## c++ file
SET(JK_FILE_LIST
	jk_file.h
	jk_file.cpp
)
SOURCE_GROUP(jk_File FILES ${JK_FILE_LIST})

## string
SET(JK_STRING_LIST
	jk_string.h
	jk_string.cpp
)
SOURCE_GROUP(jk_String FILES ${JK_STRING_LIST})

## win thread
FILE(GLOB JK_WIN_THREAD_SRC ./jk_win_thread/*.h)
SOURCE_GROUP(jk_win_thread FILES ${JK_WIN_THREAD_SRC})

## std thread
FILE(GLOB JK_STD_THREAD_SRC ./thread/*.h ./thread/*.cpp)
SOURCE_GROUP(jk_std_thread FILES ${JK_STD_THREAD_SRC})

SET(src_list
	lib_jk.h	
	jk_common.h
	${JK_FILE_LIST}
	${JK_STRING_LIST}
	${JK_WIN_THREAD_SRC}
	${JK_STD_THREAD_SRC}
)

#ADD_LIBRARY(${PROJECT_NAME} SHARED ${src_list})
ADD_LIBRARY(${PROJECT_NAME} ${BUILD_DYNAMIC_OR_STATIC} ${src_list})

IF(WIN32)
#	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
#		debug glfw3.lib optimized glfw3.lib
#	)
ENDIF(WIN32)
if(UNIX)
#	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
#		debug glfw3.so optimized glfw3.so
#	)
ENDIF(UNIX)