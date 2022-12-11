cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

set(PROJECT_NAME DES_EDE)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/bitarray/bitarray.cpp
	src/bitarray/bitarray.hpp
	src/keygen/keygen.cpp
	src/keygen/keygen.hpp
	)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)