CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(ParallelLife)
include_directories(".")
SET(CMAKE_CXX_FLAGS "-ggdb -g3 -Wall")

add_executable(run-life main.cpp)





