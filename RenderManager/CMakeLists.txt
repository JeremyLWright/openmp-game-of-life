include(ExternalProject)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

find_package(SDL REQUIRED)

ExternalProject_Add(
    SDL_gfx-2.0
    #URL http://www.ferzkopp.net/Software/SDL_gfx-2.0/SDL_gfx-2.0.22.tar.gz
    URL http://downloads.sourceforge.net/project/sdlgfx/SDL_gfx-2.0.22.tar.gz
    URL_MD5 330f291f1f09a1bdf397c9b40d92ca41
    INSTALL_DIR libs/SDL_gfx-2.0
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    )
ExternalProject_Get_Property(SDL_gfx-2.0 INSTALL_DIR)
include_directories("${INSTALL_DIR}/include")
link_directories(${INSTALL_DIR}/lib)
include_directories("/usr/include/SDL") # So the SDL_gfx library can find SDL.

add_library(RenderManager STATIC RenderManager.cpp)
add_dependencies(RenderManager SDL_gfx-2.0)
target_link_libraries(RenderManager SDL_gfx ${SDL_LIBRARY})





