cmake_minimum_required (VERSION 2.6)

set(SOURCES
    dllmain.cpp
	OpenCVProcess.h
	OpenCVProcess.cpp
	UnityPluginSource/PlatformBase.h
	UnityPluginSource/RenderAPI_OpenGLCoreES.cpp
	UnityPluginSource/RenderDevice.cpp
	UnityPluginSource/RenderDevice.h
	UnityPluginSource/RenderingPlugin.cpp
	)

file(GLOB_RECURSE SRC_RENDER
    "./Render/*.cpp"
    "./Render/*.h"
)

file(GLOB_RECURSE SRC_UNITY
    "./UnityPluginSource/Unity/*.cpp"
    "./UnityPluginSource/Unity/*.h"
)

file(GLOB_RECURSE SRC_GLEW
    "./UnityPluginSource/GLEW/*.cpp"
	"./UnityPluginSource/GLEW/*.c"
    "./UnityPluginSource/GLEW/*.h"
)

project (AVMDll)

include_directories(.)

add_library(AVMDll SHARED ${SOURCES} ${SRC_RENDER} ${SRC_UNITY} ${SRC_GLEW})

source_group("Render"            FILES ${SRC_RENDER})
source_group("Unity"            FILES ${SRC_UNITY})
source_group("GLEW"            FILES ${SRC_GLEW})

#add_subdirectory(Render)

