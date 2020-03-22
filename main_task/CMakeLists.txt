
cmake_minimum_required (VERSION 3.7)

project (a VERSION 0.20 LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wconversion")

set (CMAKE_VERBOSE_MAKEFILE on)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)




set (m_h_dir "program/headers")
set (sf_h_dir "program/space/functions/headers")
set (sg_h_dir "program/space/geometrics/headers")
set (m_s_dir "program/sources")
set (sf_s_dir "program/space/functions/sources")
set (sg_s_dir "program/space/geometrics/sources")

include_directories (${m_h_dir} ${sf_h_dir} ${sg_h_dir} program/space program/ ${Boost_INCLUDE_DIR})


set (SOURCES 
	${m_s_dir}/csv_parser.cpp ${m_h_dir}/csv_parser.h
	${m_s_dir}/function.cpp ${m_h_dir}/function.h
	program/space/init.h
	${sf_s_dir}/combinator.cpp ${sf_h_dir}/combinator.h
	${sf_s_dir}/part_of_function.cpp ${sf_h_dir}/part_of_function.h
	${sf_s_dir}/rotate.cpp ${sf_h_dir}/rotate.h
	${sf_s_dir}/velocity.cpp ${sf_h_dir}/velocity.h
	${sg_s_dir}/metrics.cpp ${sg_h_dir}/metrics.h
	${sg_s_dir}/trans_matrix.cpp ${sg_h_dir}/trans_matrix.h
	${sg_s_dir}/point.cpp ${sg_h_dir}/point.h
	${sg_s_dir}/vector.cpp ${sg_h_dir}/vector.h
	${sg_s_dir}/bz_curve.cpp ${sg_h_dir}/bz_curve.h
	${sg_s_dir}/xy_circle.cpp ${sg_h_dir}/xy_circle.h
	${sg_s_dir}/sphere.cpp ${sg_h_dir}/sphere.h
	#program/main.cpp)
	)

#program/local_main.cpp

#include_directories (program)
#include_directories (program program/headers)
#add_subdirectory (program)

#set (SOURCES program/main.cpp)


add_library ( _uir SHARED ${SOURCES})

add_executable (${PROJECT_NAME} ${SOURCES} program/main.cpp)
#add_executable (local_${PROJECT_NAME} ${SOURCES} program/local_main.cpp)

#target_link_libraries (${PROJECT_NAME} lib)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
