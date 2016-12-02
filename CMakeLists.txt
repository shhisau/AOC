cmake_minimum_required(VERSION 3.6)
project(AdventofCode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Day1/Day1.cpp)
add_executable(AdventofCode ${SOURCE_FILES})