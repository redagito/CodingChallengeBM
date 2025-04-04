cmake_minimum_required(VERSION 3.14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 20)

project(EncodingSimulation)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
