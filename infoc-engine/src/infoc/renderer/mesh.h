#pragma once

#include "infoc/core/defines.h"

#include "infoc/math/vec2.h"
#include "infoc/math/vec3.h"

#include "vertex_array.h"
#include "buffers.h"

/**
 * Mesh vertex
 */
typedef struct vertex_t
{
	/** Vertex position */
	vec3 position;
	/** Vertex texture coordinate */
	vec2 uv;
	/** Vertex normal */
	vec3 normal;
} vertex_t;

/**
 * Determines if two vertices are equal
 *
 * @param a, b The vertices to be checked
 *
 * @returns A boolean indicating if they are equal
 */
static inline bool vertex_eq(vertex_t* a, vertex_t* b)
{
	return vec3_eq(a->position, b->position) && vec2_eq(a->uv, b->uv) && vec3_eq(a->normal, b->normal);
}

/**
 * Renderable mesh
 */
typedef struct mesh_t
{
	/** Dynamic array of the vertices */
	vertex_t* vertices;
	/** Dynamic array of the indices */
	uint32_t* indices;
	/** Mesh indices count */
	size_t index_count;
	/** Mesh vertex array */
	vertex_array_t vertex_array;
	/** Mesh vertex buffer */
	vertex_buffer_t vertex_buffer;
	/** Mesh index buffer */
	index_buffer_t index_buffer;
} mesh_t;

/**
 * Appends a vertex to a mesh. If the mesh has no vertices, creates the dynamic array.
 * If a vertex is already added to the list, it appends only the index to the indices.
 *
 * @param mesh The mesh to be appended to
 * @param vertex The vertex to be appended
 */
void mesh_add_vertex(mesh_t* mesh, vertex_t* vertex);
/**
 * Stores the mesh data on the GPU
 *
 * @param mesh The mesh to store
 *
 * @returns A boolean indicating whether the operation finished succesfully
 */
bool mesh_create(mesh_t* mesh);
/**
 * Frees the mesh data from the GPU and the CPU
 *
 * @param mesh The mesh to destroy
 */
void mesh_destroy(mesh_t* mesh);
