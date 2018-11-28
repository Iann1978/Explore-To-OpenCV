#pragma once
#include "../UnityPluginSource/GLEW/glew.h"
#include <opencv2/opencv.hpp> //头文件

using namespace cv; //包含cv命名空间
class Texture
{
public:
	int				width;
	int				height;
	GLuint			texture;
	Mat				*mat = nullptr;
	static Texture*	cvTextures[32];

public:
	Texture(int width, int height, GLuint texture);
	~Texture();
};

