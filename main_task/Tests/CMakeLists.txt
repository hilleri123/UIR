
cmake_minimum_required (VERSION 3.7)

project (tests VERSION 0.20 LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set (CMAKE_VERBOSE_MAKEFILE on)

set (m_h_dir "../program/headers")
set (sf_h_dir "../program/space/functions/headers")
set (sg_h_dir "../program/space/geometrics/headers")
set (m_s_dir "../program/sources")
set (sf_s_dir "../program/space/functions/sources")
set (sg_s_dir "../program/space/geometrics/sources")

include_directories (${m_h_dir} ${sf_h_dir} ${sg_h_dir} ../program/space ../program/)


set (SOURCES 
	${m_s_dir}/csv_parser.cpp ${m_h_dir}/csv_parser.h
	${m_s_dir}/function.cpp ${m_h_dir}/function.h
	../program/space/init.h
	${sf_s_dir}/combinator.cpp ${sf_h_dir}/combinator.h
	${sf_s_dir}/part_of_function.cpp ${sf_h_dir}/part_of_function.h
	${sf_s_dir}/rotate.cpp ${sf_h_dir}/rotate.h
	${sf_s_dir}/velocity.cpp ${sf_h_dir}/velocity.h
	${sg_s_dir}/circle.cpp ${sg_h_dir}/circle.h
	${sg_s_dir}/metrics.cpp ${sg_h_dir}/metrics.h
	${sg_s_dir}/plane.cpp ${sg_h_dir}/plane.h
	${sg_s_dir}/point.cpp ${sg_h_dir}/point.h
	${sg_s_dir}/sphere.cpp ${sg_h_dir}/sphere.h
	${sg_s_dir}/vector.cpp ${sg_h_dir}/vector.h
	./test.cpp)

add_library ( _uir_tests SHARED ${SOURCES})

add_executable (${PROJECT_NAME} ${SOURCES})
