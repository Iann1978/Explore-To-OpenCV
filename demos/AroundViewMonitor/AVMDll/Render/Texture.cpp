#include "Texture.h"

Texture*	Texture::cvTextures[32];

Texture::Texture(int width, int height, GLuint texture)
{
	this->width = width;
	this->height = height;
	this->texture = texture;
	mat = nullptr;

}


Texture::~Texture()
{
}
