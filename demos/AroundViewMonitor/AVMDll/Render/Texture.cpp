#include "Texture.h"

Texture*	Texture::cvTextures[32];

Texture::Texture(GLuint texture)
{
	this->texture = texture;
	mat = nullptr;

}


Texture::~Texture()
{
}
