#-------------------------------------------------------------------------------
project(cpp_playground C CXX)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})


set(SOURCES
  templates
)


foreach(source ${SOURCES})
  add_executable(${source}
    ${CMAKE_SOURCE_DIR}/src/${source}.cpp)
  # target_link_libraries(${source} PRIVATE)
  # target_include_directories(${source} PRIVATE)
endforeach()
