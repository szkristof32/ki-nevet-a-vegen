#include "obj_loader.h"

#include "infoc/core/darray.h"

#include "file_utils.h"
#include "string_utils.h"

#include <stdlib.h>
#include <string.h>

void obj_loader_load_model(const char* filepath, mesh_t* out_mesh)
{
	memset(out_mesh, 0, sizeof(mesh_t));

	printf("Loading model %s...\n", filepath);

	char* source = file_utils_read_file(filepath);
	vec3* vertex_positions = darray_create(vec3);
	vec2* uv_coords = darray_create(vec2);
	vec3* normals = darray_create(vec3);

	char** lines = string_split(source, "\n");
	uint32_t i = 0;

	while (i < darray_count(lines))
	{
		char* line = lines[i];

		if (string_starts_with(line, "s "))
			break;

		if (string_starts_with(line, "v "))
		{
			char** tokens = string_split(line, " ");
			vec3 position = { 0 };
			position.x = (float)atof(tokens[1]);
			position.y = (float)atof(tokens[2]);
			position.z = (float)atof(tokens[3]);

			darray_push(vertex_positions, position);

			darray_destroy(tokens);
		}
		if (string_starts_with(line, "vt "))
		{
			char** tokens = string_split(line, " ");
			vec2 uv = { 0 };
			uv.x = (float)atof(tokens[1]);
			uv.y = 1.0f - (float)atof(tokens[2]);

			darray_push(uv_coords, uv);

			darray_destroy(tokens);
		}
		if (string_starts_with(line, "vn "))
		{
			char** tokens = string_split(line, " ");
			vec3 normal = { 0 };
			normal.x = (float)atof(tokens[1]);
			normal.y = (float)atof(tokens[2]);
			normal.z = (float)atof(tokens[3]);

			darray_push(normals, normal);

			darray_destroy(tokens);
		}

		i++;
	}

	i++;

	while (i < darray_count(lines))
	{
		char* line = lines[i];

		if (string_starts_with(line, "f "))
		{
			char** vertex_indices = string_split(line, " ");

			for (uint32_t j = 1; j < darray_count(vertex_indices); j++)
			{
				char** tokens = string_split(vertex_indices[j], "/");

				vertex_t vertex = { 0 };
				vertex.position = vertex_positions[atoi(tokens[0]) - 1];
				vertex.uv = uv_coords[atoi(tokens[1]) - 1];
				vertex.normal = normals[atoi(tokens[2]) - 1];

				mesh_add_vertex(out_mesh, &vertex);

				darray_destroy(tokens);
			}

			darray_destroy(vertex_indices);
		}

		i++;
	}

	mesh_create(out_mesh);

	darray_destroy(lines);

	darray_destroy(normals);
	darray_destroy(uv_coords);
	darray_destroy(vertex_positions);

	free(source);
}
