CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(ParallelLife)
find_package(Boost 1.42 REQUIRED)
add_subdirectory(RenderManager)
include_directories(".")

#SET(CMAKE_C_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icc")
#SET(CMAKE_CXX_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icpc")
SET(CMAKE_BUILD_TYPE DEBUG)
#SET(CMAKE_CXX_FLAGS_DEBUG "-debug all -openmp")
#SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -openmp")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -ggdb -fopenmp")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -openmp")

add_definitions(-DRENDER)
ExternalProject_Get_Property(SDL_gfx-2.0 INSTALL_DIR)
include_directories("${INSTALL_DIR}/include")
link_directories(${INSTALL_DIR}/lib)
link_directories(/opt/intel/composer_xe_2011_sp1.6.233/compiler/lib/intel64/)
add_executable(run-life main.cpp GameGrid.cpp GameGridParallelRow.cpp InputGenerator.cpp GameGridParallel.cpp GameGridParallelCol.cpp)
#target_link_libraries(run-life iomp5)
target_link_libraries(run-life RenderManager gomp)





