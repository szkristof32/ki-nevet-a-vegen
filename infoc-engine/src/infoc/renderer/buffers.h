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

typedef struct index_buffer_t
{
	uint32_t buffer_handle;
} index_buffer_t;

bool index_buffer_create(const uint32_t* data, size_t index_count, index_buffer_t* out_buffer);
void index_buffer_destroy(index_buffer_t* buffer);

void index_buffer_bind(const index_buffer_t* buffer);
void index_buffer_set_data(index_buffer_t* buffer, const uint32_t* data, size_t index_count);
