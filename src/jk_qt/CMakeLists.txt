cmake_minimum_required(VERSION 2.8.11)

project(jk_qt)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Core)

FILE(GLOB source_file_list *.cpp)
FILE(GLOB header_file_list *.h)

SET(src_list 
	${source_file_list}
	${header_file_list}
)


add_executable(jk_qt ${src_list})


# Use the Widgets module from Qt 5.
target_link_libraries(jk_qt Qt5::Widgets)