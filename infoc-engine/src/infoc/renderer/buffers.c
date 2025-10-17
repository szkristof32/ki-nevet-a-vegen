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

bool index_buffer_create(const uint32_t* data, size_t index_count, index_buffer_t* out_buffer)
{
	memset(out_buffer, 0, sizeof(index_buffer_t));

	glCreateBuffers(1, &out_buffer->buffer_handle);
	if (out_buffer->buffer_handle == 0)
	{
		fprintf(stderr, "Failed to create index buffer!\n");
		return false;
	}

	glNamedBufferData(out_buffer->buffer_handle, index_count * sizeof(uint32_t), NULL, GL_STATIC_DRAW);
	glNamedBufferSubData(out_buffer->buffer_handle, 0, index_count * sizeof(uint32_t), data);

	return true;
}

void index_buffer_destroy(index_buffer_t* buffer)
{
	glDeleteBuffers(1, &buffer->buffer_handle);
	memset(buffer, 0, sizeof(index_buffer_t));
}

void index_buffer_bind(const index_buffer_t* buffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->buffer_handle);
}

void index_buffer_set_data(index_buffer_t* buffer, const uint32_t* data, size_t index_count)
{
	glNamedBufferSubData(buffer->buffer_handle, 0, index_count * sizeof(uint32_t), data);
}

bool uniform_buffer_create(const void* data, size_t size, uniform_buffer_t* out_buffer)
{
	memset(out_buffer, 0, sizeof(uniform_buffer_t));

	glCreateBuffers(1, &out_buffer->buffer_handle);
	if (out_buffer->buffer_handle == 0)
	{
		fprintf(stderr, "Failed to create uniform buffer!\n");
		return false;
	}

	glNamedBufferData(out_buffer->buffer_handle, size, NULL, GL_STATIC_DRAW);
	glNamedBufferSubData(out_buffer->buffer_handle, 0, size, data);

	return true;
}

void uniform_buffer_destroy(uniform_buffer_t* buffer)
{
	glDeleteBuffers(1, &buffer->buffer_handle);
	memset(buffer, 0, sizeof(uniform_buffer_t));
}

void uniform_buffer_bind(const uniform_buffer_t* buffer)
{
	glBindBuffer(GL_UNIFORM_BUFFER, buffer->buffer_handle);
}

void uniform_buffer_bind_base(const uniform_buffer_t* buffer, uint32_t binding_point)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, buffer->buffer_handle);
}

void uniform_buffer_set_data(uniform_buffer_t* buffer, const void* data, size_t size)
{
	glNamedBufferSubData(buffer->buffer_handle, 0, size, data);
}
