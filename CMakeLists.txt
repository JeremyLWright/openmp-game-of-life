CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
include(ExternalProject)
project(ParallelLife)
find_package(SDL REQUIRED)

ExternalProject_Add(
    SDL-2.0
    URL http://www.ferzkopp.net/Software/SDL_gfx-2.0/SDL_gfx-2.0.22.tar.gz
    INSTALL_DIR libs/sdlgfx
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    )
add_subdirectory(RenderManager)
include_directories(${CMAKE_BINARY_DIR}/libs/sdlgfx/include)
link_directories(${CMAKE_BINARY_DIR}/libs/sdlgfx/lib)
include_directories(".")
include_directories("/usr/include/SDL")
SET(CMAKE_CXX_FLAGS "-ggdb -g3 -Wall")

add_executable(run-life main.cpp)
target_link_libraries(run-life RenderManager SDL_gfx ${SDL_LIBRARY})





