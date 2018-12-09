#include "CVTexture.h"


namespace cvBridge
{


	CVTexture::CVTexture(int width, int height, GLuint texture)
	{
		this->width = width;
		this->height = height;
		this->texture = texture;
		this->image = new char[2048 * 2048 * 4];
		mat = nullptr;

	}


	CVTexture::~CVTexture()
	{
		delete this->image;
	}
}
