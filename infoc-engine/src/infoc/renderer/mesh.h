#pragma once

#include "infoc/core/defines.h"

#include "infoc/math/vec2.h"
#include "infoc/math/vec3.h"

#include "vertex_array.h"
#include "buffers.h"

typedef struct vertex_t
{
	vec3 position;
	vec2 uv;
	vec3 normal;
} vertex_t;

static inline bool vertex_eq(vertex_t* a, vertex_t* b)
{
	return vec3_eq(a->position, b->position) && vec2_eq(a->uv, b->uv) && vec3_eq(a->normal, b->normal);
}

typedef struct mesh_t
{
	vertex_t* vertices; // darrray
	uint32_t* indices; // darray
	size_t index_count;
	vertex_array_t vertex_array;
	vertex_buffer_t vertex_buffer;
	index_buffer_t index_buffer;
} mesh_t;

void mesh_add_vertex(mesh_t* mesh, vertex_t* vertex);
bool mesh_create(mesh_t* mesh);
void mesh_destroy(mesh_t* mesh);
