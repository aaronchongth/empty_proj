cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_FLAGS "-g -Wall")
project(example_threading C CXX)

find_package(Threads)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
