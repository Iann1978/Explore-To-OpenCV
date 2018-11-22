#pragma once
#	include "../UnityPluginSource/GLEW/glew.h"

class Renderer_Triangle
{
	GLuint programID = 0;
	GLuint vertexbuffer = 0;

public:
	Renderer_Triangle();

public:
	void Draw();

	

};
