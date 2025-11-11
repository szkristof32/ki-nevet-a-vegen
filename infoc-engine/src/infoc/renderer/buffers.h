#pragma once

#include "infoc/core/defines.h"

/*
* Vertex buffer object
*/
typedef struct vertex_buffer_t
{
	uint32_t buffer_handle; /* OpenGL buffer handle */
} vertex_buffer_t;

/*
* Creates a vertex buffer (array buffer in OpenGL)
*
* @param data The data to be stored in the buffer
* @param size Size of the data in bytes
* @param out_buffer A pointer to a `vertex_buffer_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool vertex_buffer_create(const void* data, size_t size, vertex_buffer_t* out_buffer);
/*
* Destroys a vertex buffer
*
* @param buffer A pointer to a valid `vertex_buffer_t` struct
*/
void vertex_buffer_destroy(vertex_buffer_t* buffer);

/*
* Binds a vertex buffer
*
* @param buffer A pointer to a valid `vertex_buffer_t` struct
*/
void vertex_buffer_bind(const vertex_buffer_t* buffer);
/*
* Stores data in a vertex buffer
*
* @param buffer A pointer to a valid `vertex_buffer_t` struct
* @param data The data to be stored in the buffer
* @param size Size of the data in bytes
*/
void vertex_buffer_set_data(vertex_buffer_t* buffer, const void* data, size_t size);

/*
* Index buffer object
*/
typedef struct index_buffer_t
{
	uint32_t buffer_handle; /* OpenGL buffer handle */
} index_buffer_t;

/*
* Creates an index buffer (element array buffer in OpenGL)
*
* @param data The data to be stored in the buffer
* @param size The number of indices to be stored
* @param out_buffer A pointer to a `index_buffer_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool index_buffer_create(const uint32_t* data, size_t index_count, index_buffer_t* out_buffer);
/*
* Destroys an index buffer
*
* @param buffer A pointer to a valid `index_buffer_t` struct
*/
void index_buffer_destroy(index_buffer_t* buffer);

/*
* Binds an index buffer
*
* @param buffer A pointer to a valid `index_buffer_t` struct
*/
void index_buffer_bind(const index_buffer_t* buffer);
/*
* Stores data in an index buffer
*
* @param buffer A pointer to a valid `index_buffer_t` struct
* @param data The data to be stored in the buffer
* @param size The number of indices to be stored
*/
void index_buffer_set_data(index_buffer_t* buffer, const uint32_t* data, size_t index_count);

/*
* Uniform buffer object
*/
typedef struct uniform_buffer_t
{
	uint32_t buffer_handle;
} uniform_buffer_t;

/*
* Creates a uniform buffer
*
* @param data The data to be stored in the buffer
* @param size Size of the data in bytes
* @param out_buffer A pointer to a `uniform_buffer_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool uniform_buffer_create(const void* data, size_t size, uniform_buffer_t* out_buffer);
/*
* Destroys a uniform buffer
*
* @param buffer A pointer to a valid `uniform_buffer_t` struct
*/
void uniform_buffer_destroy(uniform_buffer_t* buffer);

/*
* Binds a uniform buffer
*
* @param buffer A pointer to a valid `uniform_buffer_t` struct
*/
void uniform_buffer_bind(const uniform_buffer_t* buffer);
/*
* Binds the base of a uniform buffer
*
* @param buffer A pointer to a valid `uniform_buffer_t` struct
*/
void uniform_buffer_bind_base(const uniform_buffer_t* buffer, uint32_t binding_point);
/*
* Stores data in a uniform buffer
*
* @param buffer A pointer to a valid `uniform_buffer_t` struct
* @param data The data to be stored in the buffer
* @param size Size of the data in bytes
*/
void uniform_buffer_set_data(uniform_buffer_t* buffer, const void* data, size_t size);
