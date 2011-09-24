CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include_directories(".")
SET(CMAKE_CXX_FLAGS "-ggdb -g3 -Wall")

add_library(RenderManager STATIC RenderManager.cpp)





