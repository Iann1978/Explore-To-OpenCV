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

	EXPORT_API void SetCVTexture(int index, int texture)
	{
		Texture::cvTextures[index] = new Texture();
		Texture::cvTextures[index]->texture = texture;
		//cvtex[index] = tex;

		//int w, h;
		//int miplevel = 0;
		//glBindTexture(GL_TEXTURE_2D, tex);
		//glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
		//glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);

		//int a = 0; 
		//int b = 0;
	}

}