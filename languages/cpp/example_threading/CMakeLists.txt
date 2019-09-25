cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_CXX_FLAGS "-g -Wall")
project(example_threading C CXX)

add_executable(${PROJECT_NAME} src/main.cpp)
