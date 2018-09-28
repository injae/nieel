cmake_minimum_required(VERSION 3.6)

project(nieel LANGUAGES CXX VERSION 0.1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(MODULE_PATH ${CMAKE_MODULE_PATH}/Modules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -pthread -fPIC")
include(${CMAKE_MODULE_PATH}/cmake_option.cmake)
include(${CMAKE_MODULE_PATH}/project_maker.cmake)
include(${CMAKE_MODULE_PATH}/utils.cmake)
get_third_party_list()
set(thirdparty 
	${Boost_LIBRARIES}
)
set(source 
	src/filesystem.cpp
	src/program_option.cpp
	src/string.cpp
	src/url.cpp
	src/version.cpp
)
build_library(nieel static "${source}" "${thirdparty}")

set(thirdparty 
	nieel
)
set(source 
	src/main.cpp
)
build_binary(nieel-main "${source}" "${thirdparty}")



