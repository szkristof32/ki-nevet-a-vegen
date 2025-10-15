#pragma once

#include "infoc/core/defines.h"

typedef enum vertex_attribute_type
{
	vertex_attribute_type_float,
	vertex_attribute_type_float2,
	vertex_attribute_type_float3,
	vertex_attribute_type_float4,
	vertex_attribute_type_int,
	vertex_attribute_type_int2,
	vertex_attribute_type_int3,
	vertex_attribute_type_int4,
	vertex_attribute_type_mat3,
	vertex_attribute_type_mat4,
	vertex_attribute_type_bool
} vertex_attribute_type;

typedef struct vertex_attribute_t
{
	vertex_attribute_type data_type;
	uint32_t offset;
} vertex_attribute_t;

typedef struct vertex_array_t
{
	uint32_t array_handle;
	vertex_attribute_t* attributes; // darray
	size_t attribute_stride;
} vertex_array_t;

bool vertex_array_create(vertex_array_t* out_vertex_array);
void vertex_array_destroy(vertex_array_t* vertex_array);

void vertex_array_bind(const vertex_array_t* vertex_array);

void vertex_array_add_attribute(vertex_array_t* vertex_array, vertex_attribute_type attribute_type);
void vertex_array_bake_layout(const vertex_array_t* vertex_array);
