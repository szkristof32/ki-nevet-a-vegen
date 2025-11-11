#pragma once

#include "infoc/core/defines.h"

#include "infoc/math/vec2.h"
#include "infoc/math/vec3.h"

#include "vertex_array.h"
#include "buffers.h"

/*
* Mesh vertex
*/
typedef struct vertex_t
{
	vec3 position; /* Vertex position */
	vec2 uv; /* Vertex texture coordinate */
	vec3 normal; /* Vertex normal */
} vertex_t;

/*
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

/*
* Renderable mesh
*/
typedef struct mesh_t
{
	vertex_t* vertices; /* Dynamic array of the vertices */
	uint32_t* indices; /* Dynamic array of the indices */
	size_t index_count; /* Mesh indices count */
	vertex_array_t vertex_array; /* Mesh vertex array */
	vertex_buffer_t vertex_buffer; /* Mesh vertex buffer */
	index_buffer_t index_buffer; /* Mesh index buffer */
} mesh_t;

/*
* Appends a vertex to a mesh. If the mesh has no vertices, creates the dynamic array.
* If a vertex is already added to the list, it appends only the index to the indices.
*
* @param mesh The mesh to be appended to
* @param vertex The vertex to be appended
*/
void mesh_add_vertex(mesh_t* mesh, vertex_t* vertex);
/*
* Stores the mesh data on the GPU
*
* @param mesh The mesh
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool mesh_create(mesh_t* mesh);
/*
* Frees the mesh data from the GPU and the CPU
*
* @param mesh The mesh
*/
void mesh_destroy(mesh_t* mesh);
