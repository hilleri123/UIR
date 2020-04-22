
cmake_minimum_required (VERSION 3.7)

project (a VERSION 0.20 LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wconversion")

set (CMAKE_VERBOSE_MAKEFILE on)


set (m_h_dir "program/headers")
set (sf_h_dir "program/space/functions/headers")
set (sg_h_dir "program/space/geometrics/headers")
set (m_s_dir "program/sources")
set (sf_s_dir "program/space/functions/sources")
set (sg_s_dir "program/space/geometrics/sources")

include_directories (${m_h_dir} ${sf_h_dir} ${sg_h_dir} program/space program/ ${Boost_INCLUDE_DIR})

set (HEADERS
	${m_h_dir}/csv_parser.h
	${m_h_dir}/function.h
	program/space/init.h
	${sf_h_dir}/combinator.h
	${sf_h_dir}/part_of_function.h
	${sf_h_dir}/rotate.h
	${sf_h_dir}/velocity.h
	${sg_h_dir}/metrics.h
	${sg_h_dir}/trans_matrix.h
	${sg_h_dir}/point.h
	${sg_h_dir}/vector.h
	${sg_h_dir}/bz_curve.h
	${sg_h_dir}/xy_circle.h
	${sg_h_dir}/sphere.h
	)

set (SOURCES 
	${m_s_dir}/csv_parser.cpp
	${m_s_dir}/function.cpp
	${sf_s_dir}/combinator.cpp
	${sf_s_dir}/part_of_function.cpp
	${sf_s_dir}/rotate.cpp
	${sf_s_dir}/velocity.cpp
	${sg_s_dir}/metrics.cpp
	${sg_s_dir}/trans_matrix.cpp
	${sg_s_dir}/point.cpp
	${sg_s_dir}/vector.cpp
	${sg_s_dir}/bz_curve.cpp
	${sg_s_dir}/xy_circle.cpp
	${sg_s_dir}/sphere.cpp
	${HEADERS}
	#program/main.cpp)
	#${m_s_dir}/csv_parser.cpp ${m_h_dir}/csv_parser.h
	#${m_s_dir}/function.cpp ${m_h_dir}/function.h
	#program/space/init.h
	#${sf_s_dir}/combinator.cpp ${sf_h_dir}/combinator.h
	#${sf_s_dir}/part_of_function.cpp ${sf_h_dir}/part_of_function.h
	#${sf_s_dir}/rotate.cpp ${sf_h_dir}/rotate.h
	#${sf_s_dir}/velocity.cpp ${sf_h_dir}/velocity.h
	#${sg_s_dir}/metrics.cpp ${sg_h_dir}/metrics.h
	#${sg_s_dir}/trans_matrix.cpp ${sg_h_dir}/trans_matrix.h
	#${sg_s_dir}/point.cpp ${sg_h_dir}/point.h
	#${sg_s_dir}/vector.cpp ${sg_h_dir}/vector.h
	#${sg_s_dir}/bz_curve.cpp ${sg_h_dir}/bz_curve.h
	#${sg_s_dir}/xy_circle.cpp ${sg_h_dir}/xy_circle.h
	#${sg_s_dir}/sphere.cpp ${sg_h_dir}/sphere.h
	#program/main.cpp)
	)

#program/local_main.cpp

#include_directories (program)
#include_directories (program program/headers)
#add_subdirectory (program)

#set (SOURCES program/main.cpp)


add_library ( _uir_shared SHARED ${SOURCES})
add_library ( _uir_static STATIC ${SOURCES})

set(HEADERS_DIR "./headers_dir")

if (WIN32)
	set(Boost_USE_STATIC_LIBS ON)
	set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/Fort SDK/lib/win32-msvc2017/boost")
	set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/Fort SDK/lib/win32-msvc2017/boost/lib")

	#set(HEADERS_DIR "C:/Work/012/...")
endif()


find_package(Boost 1.40 COMPONENTS program_options)

if (Boost_FOUND)

	add_executable (${PROJECT_NAME} ${SOURCES} program/main.cpp)
	#add_executable (local_${PROJECT_NAME} ${SOURCES} program/local_main.cpp)

	target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})

endif()

foreach (myheader_path IN LISTS HEADERS)
	get_filename_component(myheader ${myheader_path} NAME)
	message(STATUS "path = '${myheader_path}' filename = '${myheader}'")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy
		"./${myheader_path}"
		"${HEADERS_DIR}/${myheader}"
		COMMENT "Copying ${myheader_path}"
		)
endforeach()


