
cmake_minimum_required (VERSION 3.7)

project (Tests VERSION 0.20 LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wconversion")

set (CMAKE_VERBOSE_MAKEFILE on)

set (m_h_dir "../program/headers")
set (sf_h_dir "../program/space/functions/headers")
set (sg_h_dir "../program/space/geometrics/headers")
set (m_s_dir "../program/sources")
set (sf_s_dir "../program/space/functions/sources")
set (sg_s_dir "../program/space/geometrics/sources")

set (test_s_dir "source")

include_directories (${m_h_dir} ${sf_h_dir} ${sg_h_dir} ../program/space ../program ${test_s_dir})


set (SOURCES 
	${m_s_dir}/csv_parser.cpp ${m_h_dir}/csv_parser.h
	${m_s_dir}/function.cpp ${m_h_dir}/function.h
	../program/space/init.h
	${sf_s_dir}/combinator.cpp ${sf_h_dir}/combinator.h
	${sf_s_dir}/part_of_function.cpp ${sf_h_dir}/part_of_function.h
	${sf_s_dir}/rotate.cpp ${sf_h_dir}/rotate.h
	${sf_s_dir}/velocity.cpp ${sf_h_dir}/velocity.h
	#${sg_s_dir}/circle.cpp ${sg_h_dir}/circle.h
	${sg_s_dir}/metrics.cpp ${sg_h_dir}/metrics.h
	#${sg_s_dir}/plane.cpp ${sg_h_dir}/plane.h
	${sg_s_dir}/point.cpp ${sg_h_dir}/point.h
	${sg_s_dir}/sphere.cpp ${sg_h_dir}/sphere.h
	${sg_s_dir}/vector.cpp ${sg_h_dir}/vector.h
	${sg_s_dir}/trans_matrix.cpp ${sg_h_dir}/trans_matrix.h
	${sg_s_dir}/bz_curve.cpp ${sg_h_dir}/bz_curve.h
	${sg_s_dir}/xy_circle.cpp ${sg_h_dir}/xy_circle.h
	)
#${test_s_dir}/matrix_test.cpp
#${test_s_dir}/test.cpp)

#add_library ( _uir_tests SHARED ${SOURCES})

set (TEST_SOURCES
	${test_s_dir}/test.cpp
	${test_s_dir}/matrix_test.cpp
	${test_s_dir}/sphere_test.cpp
	)


list(LENGTH TEST_SOURCES len)
MATH (EXPR len "${len}-1")

#foreach (test_source num IN ZIP_LISTS TEST_SOURCES RANGE len)
foreach (num RANGE ${len})
	list (GET TEST_SOURCES ${num} test_source)
	message (${test_source} " from " ${TEST_SOURCES} " " ${len})
	message (${PROJECT_NAME}_${num} " " ${SOURCES} " " ${test_source})
	add_executable (${PROJECT_NAME}_${num} ${SOURCES} ${test_source})
endforeach()
#add_executable (${PROJECT_NAME}_1 ${SOURCES} ${test_s_dir}/test.cpp)
#add_executable (${PROJECT_NAME}_2 ${SOURCES} ${test_s_dir}/matrix_test.cpp)
