#pragma once

#include "infoc/core/defines.h"

#include "infoc/math/vec4.h"

typedef struct texture_t
{
	uint32_t texture_handle;
	uint32_t width;
	uint32_t height;
	bool is_depth;
} texture_t;

bool texture_create(const char* filepath, texture_t* out_texture);
bool texture_create_empty(uint32_t width, uint32_t height, texture_t* out_texture);
bool texture_create_format(uint32_t width, uint32_t height, uint32_t format, texture_t* out_texture);
bool texture_create_depth(uint32_t width, uint32_t height, texture_t* out_texture);
void texture_destroy(texture_t* texture);

void texture_bind(const texture_t* texture, uint32_t texture_unit);

void texture_set_data(const texture_t* texture, const void* data);

bool texture_is_valid(const texture_t* texture);

vec4 texture_read_pixel(texture_t* texture, uint32_t x, uint32_t y);
