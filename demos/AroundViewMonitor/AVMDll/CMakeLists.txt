cmake_minimum_required (VERSION 2.6)

set(SOURCES
    dllmain.cpp)

file(GLOB_RECURSE SRC_RENDER
    "./Render/*.cpp"
    "./Render/*.h"
)

project (AVMDll)

include_directories(.)

add_library(AVMDll SHARED ${SOURCES} ${SRC_RENDER})

source_group("Render"            FILES ${SRC_RENDER})

#add_subdirectory(Render)

