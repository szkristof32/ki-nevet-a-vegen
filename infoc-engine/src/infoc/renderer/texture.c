#include "texture.h"

#include "gl.h"
#include "SDL3/SDL.h"

#undef bool

#include <stdio.h>
#include <string.h>

bool texture_create(const char* filepath, texture_t* out_texture)
{
	memset(out_texture, 0, sizeof(texture_t));
	glCreateTextures(GL_TEXTURE_2D, 1, &out_texture->texture_handle);
	if (out_texture->texture_handle == 0)
	{
		fprintf(stderr, "Failed to create texture!\n");
		return false;
	}

	SDL_Surface* texuture = SDL_LoadBMP(filepath);
	if (!texuture)
	{
		fprintf(stderr, "Failed to load image from disk!\n");
		return false;
	}

	out_texture->width = texuture->w;
	out_texture->height = texuture->h;

	glTextureStorage2D(out_texture->texture_handle, 1, GL_RGB8, out_texture->width, out_texture->height);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(out_texture->texture_handle, 0, 0, 0, out_texture->width, out_texture->height, GL_RGB, GL_UNSIGNED_BYTE, texuture->pixels);

	SDL_DestroySurface(texuture);

	return true;
}

void texture_destroy(texture_t* texture)
{
	glDeleteTextures(1, &texture->texture_handle);
	memset(texture, 0, sizeof(texture_t));
}

void texture_bind(const texture_t* texture, uint32_t texture_unit)
{
	glBindTextureUnit(texture_unit, texture->texture_handle);
}
