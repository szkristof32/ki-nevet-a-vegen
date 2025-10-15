#include "buffers.h"

#include "gl.h"

#include <stdio.h>
#include <string.h>

bool vertex_buffer_create(const void* data, size_t size, vertex_buffer_t* out_buffer)
{
	memset(out_buffer, 0, sizeof(vertex_buffer_t));

	glCreateBuffers(1, &out_buffer->buffer_handle);
	if (out_buffer->buffer_handle == 0)
	{
		fprintf(stderr, "Failed to create vertex buffer!\n");
		return false;
	}

	glNamedBufferData(out_buffer->buffer_handle, size, NULL, GL_STATIC_DRAW);
	glNamedBufferSubData(out_buffer->buffer_handle, 0, size, data);

	return true;
}

void vertex_buffer_destroy(vertex_buffer_t* buffer)
{
	glDeleteBuffers(1, &buffer->buffer_handle);
	memset(buffer, 0, sizeof(vertex_buffer_t));
}

void vertex_buffer_bind(const vertex_buffer_t* buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer->buffer_handle);
}

void vertex_buffer_set_data(vertex_buffer_t* buffer, const void* data, size_t size)
{
	glNamedBufferSubData(buffer->buffer_handle, 0, size, data);
}
