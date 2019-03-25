
cmake_minimum_required (VERSION 3.7)

project (a VERSION 0.10 LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set (CMAKE_VERBOSE_MAKEFILE on)

#add_subdirectory ("0.10")

#include_directories ("0.10/" "0.10/space")
include_directories ("0.10/")

#configure_file (
#"0.10/csv_parser.h"
#"0.10/function.h"
#"0.10/space/point.h"
#"0.10/space/vector.h"
#"0.10/space/part_of_function.h"
#"0.10/space/metrix.h"
#"0.10/space/combinator.h"
#)

#set (CMAKE_CURRENT_SOURCE_DIR build/)

set (SOURCES 0.10/main.cpp)

add_library ( _uir SHARED ${SOURCES})

add_executable (${PROJECT_NAME} ${SOURCES})
