#include "mesh.h"

#include "infoc/core/darray.h"

void mesh_add_vertex(mesh_t* mesh, vertex_t* vertex)
{
	if (mesh->vertices == NULL)
		mesh->vertices = darray_create(vertex_t);
	if (mesh->indices == NULL)
		mesh->indices = darray_create(uint32_t);

	// TODO: implement sets
	for (uint32_t i = 0; i < darray_count(mesh->vertices); i++)
	{
		if (vertex_eq(vertex, &mesh->vertices[i]))
		{
			darray_push(mesh->indices, i);
			return;
		}
	}

	uint32_t index = (uint32_t)darray_count(mesh->vertices);
	darray_push(mesh->vertices, *vertex);
	darray_push(mesh->indices, index);
}

bool mesh_create(mesh_t* mesh)
{
	bool success = true;

	success &= vertex_array_create(&mesh->vertex_array);
	vertex_array_bind(&mesh->vertex_array);

	success &= vertex_buffer_create(mesh->vertices, darray_count(mesh->vertices) * sizeof(vertex_t), &mesh->vertex_buffer);
	vertex_buffer_bind(&mesh->vertex_buffer);
	vertex_array_add_attribute(&mesh->vertex_array, vertex_attribute_type_float3);
	vertex_array_add_attribute(&mesh->vertex_array, vertex_attribute_type_float2);
	vertex_array_add_attribute(&mesh->vertex_array, vertex_attribute_type_float3);
	vertex_array_add_attribute(&mesh->vertex_array, vertex_attribute_type_float4);
	vertex_array_bake_layout(&mesh->vertex_array);

	success &= index_buffer_create(mesh->indices, darray_count(mesh->indices), &mesh->index_buffer);
	index_buffer_bind(&mesh->index_buffer);

	mesh->index_count = darray_count(mesh->indices);

	return success;
}
