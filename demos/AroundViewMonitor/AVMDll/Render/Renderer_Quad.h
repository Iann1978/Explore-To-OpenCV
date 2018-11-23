#pragma once
#	include "../UnityPluginSource/GLEW/glew.h"

class Renderer_Quad
{
public:
	GLuint programID = 0;
	GLuint vertexbuffer = 0;
	GLuint texture;

public:
	Renderer_Quad();

public:
	void Draw();
};
