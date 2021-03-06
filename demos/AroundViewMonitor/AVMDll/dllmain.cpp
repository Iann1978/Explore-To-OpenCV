// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "UnityPluginSource/GLEW/glew.h"
#define EXPORT_API __declspec(dllexport)
#include "Render\CVTexture.h"
#include "OpenCVProcess.h"
using namespace cvBridge;
extern "C" {
	

	EXPORT_API int GetVersion() 
	{
		return 15;
	}

	EXPORT_API void SetCVTexture(int index, int width, int height, int texture)
	{
		OpenCVProcess::cvTextures[index] = new CVTexture(width, height, texture);
	}

	EXPORT_API void SetInteger(int index, int value)
	{
		OpenCVProcess::intValues[index] = value;
	}

}