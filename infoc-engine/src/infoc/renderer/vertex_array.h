#pragma once

#include "infoc/core/defines.h"

/*
* Vertex attribute data type
*/
typedef enum vertex_attribute_type
{
	vertex_attribute_type_float,	/* Float */
	vertex_attribute_type_float2,	/* Two component float vector */
	vertex_attribute_type_float3,	/* Three component float vector */
	vertex_attribute_type_float4,	/* Four component float vector */
	vertex_attribute_type_int,		/* Int */
	vertex_attribute_type_int2,		/* Two component int vector */
	vertex_attribute_type_int3,		/* Three component int vector */
	vertex_attribute_type_int4,		/* Four component int vector */
	vertex_attribute_type_mat3,		/* 3x3 matrix */
	vertex_attribute_type_mat4,		/* 4x4 matrix */
	vertex_attribute_type_bool		/* Boolean */
} vertex_attribute_type;

/*
* Vertex attribute
*/
typedef struct vertex_attribute_t
{
	vertex_attribute_type data_type; /* Data type */
	uint32_t offset; /* Offset from the beginning of the vertex */
} vertex_attribute_t;

/*
* Vertex array object
*/
typedef struct vertex_array_t
{
	uint32_t array_handle; /* OpenGL array handle */
	vertex_attribute_t* attributes; /* Dynamic array of vertex attributes */
	size_t attribute_stride; /* Length of each vertex in bytes */
} vertex_array_t;

/*
* Creates a vertex array
*
* @param out_vertex_array A pointer to a `vertex_array_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool vertex_array_create(vertex_array_t* out_vertex_array);
/*
* Destroys a vertex array
*
* @param vertex_array A pointer to a valid `vertex_array_t` struct
*/
void vertex_array_destroy(vertex_array_t* vertex_array);

/*
* Binds a vertex array
*
* @param vertex_array A pointer to a valid `vertex_array_t` struct
*/
void vertex_array_bind(const vertex_array_t* vertex_array);

/*
* Appends a vertex attribute to a vertex array
*
* @param vertex_array A pointer to a valid `vertex_array_t` struct
* @param attribute_type Data type of the attribute
*/
void vertex_array_add_attribute(vertex_array_t* vertex_array, vertex_attribute_type attribute_type);
/*
* Finalises the vertex layout of a vertex array
*
* @param vertex_array A pointer to a valid `vertex_array_t` struct
*/
void vertex_array_bake_layout(const vertex_array_t* vertex_array);
