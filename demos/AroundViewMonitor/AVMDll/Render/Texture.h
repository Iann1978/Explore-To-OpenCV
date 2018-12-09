#pragma once
#include "../UnityPluginSource/GLEW/glew.h"
#include <opencv2/opencv.hpp>

namespace cvBridge
{
	using namespace cv; //°üº¬cvÃüÃû¿Õ¼ä
	class Texture
	{
	public:
		int				width = 0;
		int				height = 0;
		GLuint			texture = 0;
		Mat				*mat = nullptr;
		char			*image = nullptr;
		

	public:
		Texture(int width, int height, GLuint texture);
		~Texture();
	};
}

