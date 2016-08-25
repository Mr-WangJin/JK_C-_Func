CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(JK_CPP_FUNC)

MESSAGE(STATUS "This is Project's root direction " ${PROJECT_SOURCE_DIR})

#Set output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
MAKE_DIRECTORY(${EXECUTABLE_OUTPUT_PATH})
MESSAGE(STATUS "This is EXECUTABLE_OUTPUT_PATH " ${EXECUTABLE_OUTPUT_PATH})

#SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
MAKE_DIRECTORY(${LIBRARY_OUTPUT_PATH})
MESSAGE(STATUS "This is LIBRARY_OUTPUT_PATH " ${LIBRARY_OUTPUT_PATH})

# Installation stuff
SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

# Set the build postfix extension according to what configuration is being built.
IF (CMAKE_BUILD_TYPE MATCHES "Release")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
ELSEIF (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}")
ELSEIF(CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
ELSEIF(CMAKE_BUILD_TYPE MATCHES "Debug")
    SET(CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
ELSE()
    SET(CMAKE_BUILD_POSTFIX "")
ENDIF()

#set Install Path
#SET(CMAKE_INSTALL_PREFIX /)

#add additional search paths here
#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")
#SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} CACHE STRING "(EXPERIMENTAL) You may add additional search paths here. Use ; to separate multiple paths.")


#Dynamic vs Static Linking
OPTION(BUILD_DYNAMIC "Set to On to build project for dynamic linking. Use OFF for static." ON)
IF (BUILD_DYNAMIC)
	SET(BUILD_DYNAMIC_OR_STATIC "SHARED")
ELSE ()
	SET(BUILD_DYNAMIC_OR_STATIC "STATIC")
ENDIF()


ADD_SUBDIRECTORY(src)