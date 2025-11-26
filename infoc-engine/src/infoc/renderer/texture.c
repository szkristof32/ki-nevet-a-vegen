#include "texture.h"

#include "gl.h"
#include <SDL_image.h>

#undef bool

#include <stdio.h>
#include <string.h>

bool texture_create(const char* filepath, texture_t* out_texture)
{
	memset(out_texture, 0, sizeof(texture_t));
	glCreateTextures(GL_TEXTURE_2D, 1, &out_texture->texture_handle);
	check_error(out_texture->texture_handle == 0, "Failed to create texture!");

	printf("Loading texture %s...\n", filepath);

	SDL_Surface* texture = IMG_Load(filepath);
	check_error(!texture, "Failed to load image from disk!");

	out_texture->width = texture->w;
	out_texture->height = texture->h;
	out_texture->is_depth = false;

	glTextureStorage2D(out_texture->texture_handle, 1, GL_RGBA8, out_texture->width, out_texture->height);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(out_texture->texture_handle, 0, 0, 0, out_texture->width, out_texture->height, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);

	SDL_FreeSurface(texture);

	return true;
}

bool texture_create_empty(uint32_t width, uint32_t height, texture_t* out_texture)
{
	memset(out_texture, 0, sizeof(texture_t));
	glCreateTextures(GL_TEXTURE_2D, 1, &out_texture->texture_handle);
	check_error(out_texture->texture_handle == 0, "Failed to create texture!");

	out_texture->width = width;
	out_texture->height = height;
	out_texture->is_depth = false;

	glTextureStorage2D(out_texture->texture_handle, 1, GL_RGB8, out_texture->width, out_texture->height);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;
}

bool texture_create_format(uint32_t width, uint32_t height, uint32_t format, texture_t* out_texture)
{
	memset(out_texture, 0, sizeof(texture_t));
	glCreateTextures(GL_TEXTURE_2D, 1, &out_texture->texture_handle);
	check_error(out_texture->texture_handle == 0, "Failed to create texture!");

	out_texture->width = width;
	out_texture->height = height;
	out_texture->is_depth = false;

	glTextureStorage2D(out_texture->texture_handle, 1, format, out_texture->width, out_texture->height);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;
}

bool texture_create_depth(uint32_t width, uint32_t height, texture_t* out_texture)
{
	memset(out_texture, 0, sizeof(texture_t));
	glCreateTextures(GL_TEXTURE_2D, 1, &out_texture->texture_handle);
	check_error(out_texture->texture_handle == 0, "Failed to create texture!");

	out_texture->width = width;
	out_texture->height = height;
	out_texture->is_depth = true;

	glTextureStorage2D(out_texture->texture_handle, 1, GL_DEPTH24_STENCIL8, out_texture->width, out_texture->height);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(out_texture->texture_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

void texture_set_data(const texture_t* texture, const void* data)
{
	uint32_t format = texture->is_depth ? GL_DEPTH_STENCIL : GL_RGB;
	glTextureSubImage2D(texture->texture_handle, 0, 0, 0, texture->width, texture->height, format, GL_UNSIGNED_BYTE, data);
}

void texture_set_data_format(const texture_t* texture, const void* data, uint32_t format)
{
	glTextureSubImage2D(texture->texture_handle, 0, 0, 0, texture->width, texture->height, format, GL_UNSIGNED_BYTE, data);
}

bool texture_is_valid(const texture_t* texture)
{
	return texture->texture_handle != 0;
}

vec4 texture_read_pixel(texture_t* texture, uint32_t x, uint32_t y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return vec4_scalar(0);

	vec4 pixel = vec4_scalar(0.0f);
	glGetTextureSubImage(texture->texture_handle, 0, x, y, 0, 1, 1, 1, GL_RGBA, GL_FLOAT, sizeof(pixel), &pixel);

	return pixel;
}

uint32_t texture_read_pixel_uint(texture_t* texture, uint32_t x, uint32_t y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return 0;

	uint32_t pixel;
	glGetTextureSubImage(texture->texture_handle, 0, x, y, 0, 1, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, sizeof(pixel), &pixel);

	return pixel;
}
