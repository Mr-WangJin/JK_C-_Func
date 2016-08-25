
SET(PROJECT_NAME "JK_TEST")

ADD_DEFINITIONS(-D_JK_BUILD_DLL)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/jk_cpp_func/)
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
		debug ${LIBRARY_OUTPUT_PATH}/Debug/JK_CPP_FUNCd.lib optimized ${LIBRARY_OUTPUT_PATH}/Realse/JK_CPP_FUNC.lib
	)
ENDIF(WIN32)
if(UNIX)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
		debug Debug/JK_CPP_FUNCd.so optimized Realse/JK_CPP_FUNC.so
	)
ENDIF(UNIX)