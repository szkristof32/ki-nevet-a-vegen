#include "vertex_array.h"

#include "infoc/core/darray.h"
#include "gl.h"

#include <string.h>

bool vertex_array_create(vertex_array_t* out_vertex_array)
{
	memset(out_vertex_array, 0, sizeof(vertex_array_t));

	glCreateVertexArrays(1, &out_vertex_array->array_handle);
	check_error(out_vertex_array->array_handle == 0, "Failed to create vertex array!");

	out_vertex_array->attributes = darray_create(vertex_attribute_t);
	check_error(out_vertex_array->attributes == NULL, "Failed to create darray for vertex attributes!");

	return true;
}

void vertex_array_destroy(vertex_array_t* vertex_array)
{
	darray_destroy(vertex_array->attributes);
	glDeleteVertexArrays(1, &vertex_array->array_handle);
	memset(vertex_array, 0, sizeof(vertex_array_t));
}

void vertex_array_bind(const vertex_array_t* vertex_array)
{
	glBindVertexArray(vertex_array->array_handle);
}

static uint32_t _vertex_attribute_type_size(vertex_attribute_type type)
{
	switch (type)
	{
		case vertex_attribute_type_float:	return 4;
		case vertex_attribute_type_float2:	return 2 * 4;
		case vertex_attribute_type_float3:	return 3 * 4;
		case vertex_attribute_type_float4:	return 4 * 4;
		case vertex_attribute_type_int:		return 4;
		case vertex_attribute_type_int2:	return 2 * 4;
		case vertex_attribute_type_int3:	return 3 * 4;
		case vertex_attribute_type_int4:	return 4 * 4;
		case vertex_attribute_type_mat3:	return 3 * 4;
		case vertex_attribute_type_mat4:	return 4 * 4;
		case vertex_attribute_type_bool:	return 1;
	}

	log_error("Invalid vertex_attribute_type!");
	return 0;
}

static uint32_t _vertex_attribute_type_component_count(vertex_attribute_type type)
{
	switch (type)
	{
		case vertex_attribute_type_float:	return 1;
		case vertex_attribute_type_float2:	return 2;
		case vertex_attribute_type_float3:	return 3;
		case vertex_attribute_type_float4:	return 4;
		case vertex_attribute_type_int:		return 1;
		case vertex_attribute_type_int2:	return 2;
		case vertex_attribute_type_int3:	return 3;
		case vertex_attribute_type_int4:	return 4;
		case vertex_attribute_type_mat3:	return 3 * 3;
		case vertex_attribute_type_mat4:	return 4 * 4;
		case vertex_attribute_type_bool:	return 1;
	}

	log_error("Invalid vertex_attribute_type!");
	return 0;
}

static uint32_t _vertex_attribute_type_gl_type(vertex_attribute_type type)
{
	switch (type)
	{
		case vertex_attribute_type_float:
		case vertex_attribute_type_float2:
		case vertex_attribute_type_float3:
		case vertex_attribute_type_float4:
			return GL_FLOAT;
		case vertex_attribute_type_int:
		case vertex_attribute_type_int2:
		case vertex_attribute_type_int3:
		case vertex_attribute_type_int4:
			return GL_INT;
		case vertex_attribute_type_mat3:
		case vertex_attribute_type_mat4:
			return GL_FLOAT;
		case vertex_attribute_type_bool:
			return GL_INT;
	}

	log_error("Invalid vertex_attribute_type!");
	return 0;
}

void vertex_array_add_attribute(vertex_array_t* vertex_array, vertex_attribute_type attribute_type)
{
	vertex_attribute_t attribute = { 0 };
	attribute.data_type = attribute_type;
	attribute.offset = (uint32_t)vertex_array->attribute_stride;

	darray_push(vertex_array->attributes, attribute);
	vertex_array->attribute_stride += _vertex_attribute_type_size(attribute.data_type);
}

void vertex_array_bake_layout(const vertex_array_t* vertex_array)
{
	for (uint32_t i = 0; i < darray_count(vertex_array->attributes); i++)
	{
		const vertex_attribute_t* attribute = &vertex_array->attributes[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, _vertex_attribute_type_component_count(attribute->data_type),
			_vertex_attribute_type_gl_type(attribute->data_type), false,
			(uint32_t)vertex_array->attribute_stride, (const void*)(uint64_t)attribute->offset);
	}
}
