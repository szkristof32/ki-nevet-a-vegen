#pragma once

#include "infoc/core/defines.h"

typedef struct vertex_buffer_t
{
	uint32_t buffer_handle;
} vertex_buffer_t;

bool vertex_buffer_create(const void* data, size_t size, vertex_buffer_t* out_buffer);
void vertex_buffer_destroy(vertex_buffer_t* buffer);

void vertex_buffer_bind(const vertex_buffer_t* buffer);
void vertex_buffer_set_data(vertex_buffer_t* buffer, const void* data, size_t size);
