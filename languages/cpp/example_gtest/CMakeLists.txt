cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_CXX_FLAGS "-g -Wall")
project(bank_account C CXX)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available
if (test)
  add_subdirectory(test)
endif()
