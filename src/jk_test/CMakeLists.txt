
SET(PROJECT_NAME "jk_test")

ADD_DEFINITIONS(-D_JK_BUILD_DLL)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/JKCore/)
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH}/Debug/)

FILE(GLOB source_file_list *.cpp)
FILE(GLOB header_file_list *.h)
	
SET(src_list 
	${source_file_list}
	${header_file_list}
)

#ADD_LIBRARY(${PROJECT_NAME} SHARED ${src_list})
ADD_EXECUTABLE(${PROJECT_NAME} ${src_list})

IF(WIN32)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
		debug ${LIBRARY_OUTPUT_PATH}/Debug/JKCored.lib optimized ${LIBRARY_OUTPUT_PATH}/Release/JKCore.lib
	)
ENDIF(WIN32)
if(UNIX)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
		debug Debug/jk_cppd.so optimized Realse/JKCore.so
	)
ENDIF(UNIX)