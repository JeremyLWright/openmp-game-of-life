CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(ParallelLife)
find_package(Boost 1.42 REQUIRED)
add_subdirectory(RenderManager)
include_directories(".")


SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb -g3 -Wall -pedantic -fopenmp")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -fopenmp")

ExternalProject_Get_Property(SDL_gfx-2.0 INSTALL_DIR)
include_directories("${INSTALL_DIR}/include")
link_directories(${INSTALL_DIR}/lib)
add_executable(run-life main.cpp GameGrid.cpp GameGridParallelRow.cpp InputGenerator.cpp GameGridParallel.cpp GameGridParallelCol.cpp)
target_link_libraries(run-life RenderManager)





