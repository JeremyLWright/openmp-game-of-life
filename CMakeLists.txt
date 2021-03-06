CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(ParallelLife)
find_package(Boost 1.42 REQUIRED)
if(${USE_INTEL})
    message("Using Intel")
    SET(CMAKE_C_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icc")
    SET(CMAKE_CXX_COMPILER "/opt/intel/composer_xe_2011_sp1/bin/icpc")
    SET(CMAKE_CXX_FLAGS_DEBUG "-debug all -openmp")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -openmp")
    link_directories(/opt/intel/composer_xe_2011_sp1.6.233/compiler/lib/intel64/)
else()
    message("Using GCC")
    SET(CMAKE_CXX_FLAGS "-g3 -ggdb -Wall -fopenmp")
endif()

    include_directories(".")
if(${RENDER})
    add_subdirectory(RenderManager)
    ExternalProject_Get_Property(SDL_gfx-2.0 INSTALL_DIR)
    include_directories(".")
    include_directories("${INSTALL_DIR}/include")
    link_directories(${INSTALL_DIR}/lib)
    add_definitions(-DRENDER)
else()
    add_definitions(-DNRENDER)
endif()

SET(GameSources GameGrid.cpp GameGridParallelRow.cpp InputGenerator.cpp GameGridParallel.cpp GameGridParallelCol.cpp)

add_executable(run-life main.cpp ${GameSources})
add_executable(nsweep nsweep.cpp ${GameSources})
add_executable(sm_nsweep small_nsweep.cpp ${GameSources})
if(${USE_INTEL})
    target_link_libraries(run-life iomp5)
else()
    if(${RENDER})
        target_link_libraries(run-life RenderManager gomp)
    else()
        target_link_libraries(run-life gomp)
        target_link_libraries(nsweep gomp)
        target_link_libraries(sm_nsweep gomp)
    endif()
endif()





