CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(BalancedThreads)
include_directories(".")

SET(CMAKE_C_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icc")
SET(CMAKE_CXX_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icpc")
SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_CXX_FLAGS_DEBUG "-debug all -openmp")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -openmp")

link_directories(/opt/intel/composer_xe_2011_sp1.6.233/compiler/lib/intel64/)
add_executable(threads main.cpp)
target_link_libraries(threads iomp5)

add_executable(input-mm mm.cc)
target_link_libraries(input-mm iomp5)



