#pragma once
#include "../UnityPluginSource/GLEW/glew.h"
#include <opencv2/opencv.hpp> //ͷ�ļ�

using namespace cv; //����cv�����ռ�
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

