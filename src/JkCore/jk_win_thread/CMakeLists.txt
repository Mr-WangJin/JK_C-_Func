
SET(PROJECT_NAME "JK_WIN_THREAD")

ADD_DEFINITIONS(-D_JK_BUILD_DLL)

FILE(GLOB source_file_list *.cpp)
FILE(GLOB header_file_list *.h)

SET(JK_FILE_LIST
	jk_file.h
	jk_file.cpp
)
SOURCE_GROUP(jk_File FILES ${JK_FILE_LIST})

SET(JK_STRING_LIST
	jk_string.h
	jk_string.cpp
)
+(jk_String FILES ${JK_STRING_LIST})


SET(src_list
	lib_jk.h	jk_common.h
	${JK_FILE_LIST}
	${JK_STRING_LIST}
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