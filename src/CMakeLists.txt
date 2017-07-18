
MACRO(START_EXAMPLE)

    INCLUDE_DIRECTORIES($ENV{GLFW_HOME}/include)
	LINK_DIRECTORIES($ENV{GLFW_HOME}/lib)
	INCLUDE_DIRECTORIES($ENV{GLEW_HOME}/include)
	LINK_DIRECTORIES($ENV{GLEW_HOME}/lib/Release/Win32)
	INCLUDE_DIRECTORIES($ENV{GLM_HOME}/include)

	
	FILE(GLOB source_file_list ${PROJECT_NAME}/*.cpp)
	FILE(GLOB header_file_list ${PROJECT_NAME}/*.h)
	MESSAGE(STATUS  ${PROJECT_NAME}-"this is source file list: " ${source_file_list})
	
	SET(file_list 
	${source_file_list}
	${header_file_list}
	${COMMON_LIST}
	)

	ADD_EXECUTABLE(${PROJECT_NAME} ${file_list})
IF(WIN32)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
		debug glfw3.lib optimized glfw3.lib
		debug glew32s.lib optimized glew32s.lib
		debug opengl32.lib optimized opengl32.lib
		debug glu32.lib optimized glu32.lib
		glu32

	)
ENDIF(WIN32)
if(UNIX)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
		debug glfw3.so optimized glfw3.so

	)
ENDIF(UNIX)

ENDMACRO(START_EXAMPLE)

#MESSAGE(STATUS "This is additionan include path" ${CMAKE_INCLUDE_PATH})


ADD_SUBDIRECTORY(JkCore)
#ADD_SUBDIRECTORY(jk_test)
#ADD_SUBDIRECTORY(jk_qt)

#SET(PROJECT_NAME "particle01")
#START_EXAMPLE()


