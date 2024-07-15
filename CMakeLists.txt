cmake_minimum_required(VERSION 3.24)
project(Soft_heap_proyecto)

set(CMAKE_CXX_STANDARD 17)
find_package(PkgConfig REQUIRED)
pkg_search_module(ALLEGRO REQUIRED allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5 allegro_primitives-5)
include_directories(${ALLEGRO_INCLUDE_DIRS})


add_executable(Soft_heap_proyecto main.cpp softheap.h )
add_executable(Allegro allegro.cpp funciones_pac.h)


target_link_libraries(Allegro
        C:/msys64/mingw64/lib/liballegro.dll.a
        C:/msys64/mingw64/lib/liballegro_main.dll.a
        C:/msys64/mingw64/lib/liballegro_image.dll.a
        C:/msys64/mingw64/lib/liballegro_font.dll.a
        C:/msys64/mingw64/lib/liballegro_ttf.dll.a
        C:/msys64/mingw64/lib/liballegro_audio.dll.a
        C:/msys64/mingw64/lib/liballegro_acodec.dll.a
        C:/msys64/mingw64/lib/liballegro_primitives.dll.a
        )