#include "Texture.h"


namespace cvBridge
{


	Texture::Texture(int width, int height, GLuint texture)
	{
		this->width = width;
		this->height = height;
		this->texture = texture;
		this->image = new char[2048 * 2048 * 4];
		mat = nullptr;

	}


	Texture::~Texture()
	{
		delete this->image;
	}
}
