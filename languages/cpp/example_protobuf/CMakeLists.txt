CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(example_protoc_project_build)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror")

include(FindProtobuf)
find_package(Protobuf REQUIRED)

add_subdirectory(proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD_17)
target_link_libraries(main proto ${PROTOBUF_LIBRARIES})

