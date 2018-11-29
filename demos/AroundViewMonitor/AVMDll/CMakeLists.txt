cmake_minimum_required (VERSION 2.6)

set(SOURCES
    dllmain.cpp)
project (AVMDll)
add_library(AVMDll SHARED ${SOURCES})
