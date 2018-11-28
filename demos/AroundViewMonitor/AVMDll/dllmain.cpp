// dllmain.cpp : 定义 DLL 应用程序的入口点。

#include "UnityPluginSource/GLEW/glew.h"
#define EXPORT_API __declspec(dllexport)
#include "Render\Texture.h"
extern "C" {

	//static int cvtex[4];

	EXPORT_API int GetVersion() 
	{
		return 15;
	}

	EXPORT_API void SetCVTexture(int index, int width, int height, int texture)
	{
		Texture::cvTextures[index] = new Texture(width, height, texture);
	}

}