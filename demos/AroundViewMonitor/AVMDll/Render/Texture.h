#pragma once
#include "../UnityPluginSource/GLEW/glew.h"
class Texture
{
public:
	int				width;
	int				height;
	GLuint			texture;
	static Texture*	cvTextures[32];
public:
	Texture();
	~Texture();
};

