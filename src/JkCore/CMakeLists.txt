
SET(PROJECT_NAME "JKCore")

ADD_DEFINITIONS(-DJK_Core_DLL)

## common 公共操作
FILE(GLOB JK_COMMON_LIST ./JKCommon/*)
SOURCE_GROUP(JKCommon FILES ${JK_COMMON_LIST})

FILE(GLOB JK_Framework_LIST ./JKFramework/*)
SOURCE_GROUP(JKFramework FILES ${JK_Framework_LIST})

FILE(GLOB JK_Exception_LIST ./JKException/*)
SOURCE_GROUP(JKException FILES ${JK_Exception_LIST})

FILE(GLOB JK_Log_LIST ./JKLog/*)
SOURCE_GROUP(JKLog FILES ${JK_Log_LIST})

## c++ file 所有关于文件的操作
FILE(GLOB JK_FILE_LIST ./JKFile/*)
SOURCE_GROUP(JKFile FILES ${JK_FILE_LIST})

## string 所有关于字符串的操作
FILE(GLOB JK_Util_LIST ./JKUtil/*)
SOURCE_GROUP(JKUtil FILES ${JK_Util_LIST})

## error 
FILE(GLOB JK_ERROR_LIST ./JKError/*)
SOURCE_GROUP(JKError FILES ${JK_ERROR_LIST})

## thread
FILE(GLOB JK_THREAD_LIST ./JKThread/*)
SOURCE_GROUP(JKThread FILES ${JK_THREAD_LIST})

## algorithm
FILE(GLOB JK_ALGORITHM_LIST ./JKAlgorithm/*.h ./JKAlgorithm/*.cpp)
FILE(GLOB JK_Curve_SRC ./JKAlgorithm/Curve/*.h ./JKAlgorithm/Curve/*.cpp)
SOURCE_GROUP(JKAlgorithm FILES ${JK_ALGORITHM_LIST})
SOURCE_GROUP(JKAlgorithm\\JKCurve FILES ${JK_Curve_SRC})

## command
FILE(GLOB JK_COMMAND_LIST ./JKCommand/*)
SOURCE_GROUP(JKCommand FILES ${JK_COMMAND_LIST})

## framework
FILE(GLOB JK_FRAMEWORK_SRC ./JKFramework/*.h ./JKFramework/*.cpp)
FILE(GLOB JK_SmartPtr_SRC ./JKFramework/SmartPtr/*.h ./JKFramework/SmartPtr/*.cpp)
SOURCE_GROUP(JKFramework FILES ${JK_FRAMEWORK_SRC})
SOURCE_GROUP(JKFramework\\JKSmartPtr FILES ${JK_SmartPtr_SRC})

SET(src_list
	lib_jk.h	
	${JK_COMMON_LIST}
	${JK_Framework_LIST}
	${JK_Log_LIST}
	${JK_FILE_LIST}
	${JK_Util_LIST}
	${JK_THREAD_LIST}
	${JK_FRAMEWORK_SRC}
	${JK_ERROR_LIST}
	${JK_Exception_LIST}
	${JK_SmartPtr_SRC}
	${JK_ALGORITHM_LIST}
	${JK_Curve_SRC}
	${JK_COMMAND_LIST}
)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rdParty/glm/)
#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/build/bin/Debug/)

#ADD_LIBRARY(${PROJECT_NAME} SHARED ${src_list})
INCLUDE_DIRECTORIES( ./ )
ADD_LIBRARY(${PROJECT_NAME} ${BUILD_DYNAMIC_OR_STATIC} ${src_list})

IF(WIN32)
#	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
#		debug 
#	)
#	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
#		debug ${PROJECT_SOURCE_DIR}/build/bin/Debug/lib_json.lib optimized ${PROJECT_SOURCE_DIR}/3rdParty/jsoncpp/lib/x64/Release/lib_json.lib
#	)
ENDIF(WIN32)
if(UNIX)
#	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
#		debug glfw3.so optimized glfw3.so
#	)
ENDIF(UNIX)










