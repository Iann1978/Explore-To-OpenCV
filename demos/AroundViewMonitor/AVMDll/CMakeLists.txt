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

# solution name
project (AVMDll)

# include directores
include_directories(.)

# predefined macro
ADD_DEFINITIONS(-DGLEW_STATIC)

# add libs
LINK_LIBRARIES("E:/test/opencv/opencv/build/x64/vc15/lib/opencv_world342d.lib" "opengl32.lib")



# dll project with name AVMDll
add_library(AVMDll SHARED ${SOURCES} ${SRC_RENDER} ${SRC_UNITY} ${SRC_GLEW})



source_group("Render"            FILES ${SRC_RENDER})
source_group("Unity"            FILES ${SRC_UNITY})
source_group("GLEW"            FILES ${SRC_GLEW})

#add_subdirectory(Render)



# post event
add_custom_command(
TARGET AVMDll 
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy  "E:/git/Explore-To-OpenCV/demos/AroundViewMonitor/AVMDll/build/Debug/AVMDll.dll" "E:/git/Explore-To-OpenCV/demos/AroundViewMonitor/AVMUnity/Assets/"
)
