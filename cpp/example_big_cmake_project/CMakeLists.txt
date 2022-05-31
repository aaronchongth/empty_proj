cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 17)

#-------------------------------------------------------------------------------
# Project setup
#-------------------------------------------------------------------------------
project(playground C CXX)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# libraries
add_subdirectory(src/djikstra)

# executables
add_subdirectory(src/templates)

