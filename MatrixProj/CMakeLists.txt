CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(BalancedThreads)
include_directories(".")
SET(CMAKE_BUILD_TYPE DEBUG)
find_package(GTest)

if(${USE_INTEL})
    message("Using Intel")
    SET(CMAKE_C_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icc")
    SET(CMAKE_CXX_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icpc")
    SET(CMAKE_CXX_FLAGS_DEBUG "-debug all -openmp")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -openmp")
link_directories(/opt/intel/composer_xe_2011_sp1.6.233/compiler/lib/intel64/)
else()
    message("Using GCC")
    SET(CMAKE_XX_FLAGS "-g3 -ggdb -Wall -fopenmp")
endif()


add_library(matrix matrix.cpp)
add_executable(threads main.cpp)
target_link_libraries(threads matrix)
add_executable(input-mm mm.cc)
if(${USE_INTEL})
    target_link_libraries(threads iomp5)
    target_link_libraries(input-mm iomp5)
else()
    target_link_libraries(threads gomp)
    target_link_libraries(input-mm gomp)
endif()

if(GTEST_FOUND)
    add_custom_target(test 
        COMMAND test_balanced
        DEPENDS test_balanced)
    add_executable(test_balanced tests.cpp)
    target_link_libraries(test_balanced ${GTEST_BOTH_LIBRARIES} pthread matrix gomp)

endif()
