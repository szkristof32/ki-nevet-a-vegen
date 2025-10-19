#pragma once

#include "infoc/core/defines.h"

typedef struct texture_t
{
	uint32_t texture_handle;
	uint32_t width;
	uint32_t height;
} texture_t;

bool texture_create(const char* filepath, texture_t* out_texture);
void texture_destroy(texture_t* texture);

void texture_bind(const texture_t* texture, uint32_t texture_unit);
