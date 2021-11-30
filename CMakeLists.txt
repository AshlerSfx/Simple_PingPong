cmake_minimum_required(VERSION 3.17)
project(Ping_Pong)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${GCC_COVERAGE_COMPILE_FLAGS}" )
add_executable(Ping_Pong main.cpp)