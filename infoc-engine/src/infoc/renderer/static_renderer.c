#include "static_renderer.h"

#include "infoc/core/engine.h"

#include "infoc/math/mat4.h"
#include "infoc/math/utilities.h"

#include "shader.h"
#include "texture.h"
#include "gl.h"

typedef struct matrices_t
{
	mat4 projection;
	mat4 view;
} matrices_t;

typedef struct static_renderer_t
{
	shader_t shader;
	texture_t texture;

	matrices_t matrices;
	uniform_buffer_t matrices_uniform;
} static_renderer_t;

static static_renderer_t* s_static_renderer = NULL;

bool static_renderer_init()
{
	arena_allocator_t* allocator = engine_get_allocator();
	s_static_renderer = arena_allocator_allocate(allocator, sizeof(static_renderer_t));
	if (s_static_renderer == NULL)
	{
		fprintf(stderr, "Failed to initialise static renderer!\n");
		return false;
	}

	bool success = shader_create("assets/shaders/static_shader.vert", "assets/shaders/static_shader.frag", &s_static_renderer->shader);
	if (!success)
	{
		fprintf(stderr, "Failed to create static shader!\n");
		return false;
	}

	success = texture_create("assets/images/test.bmp", &s_static_renderer->texture);
	if (!success)
	{
		fprintf(stderr, "Failed to load image!\n");
		return false;
	}

	success = uniform_buffer_create(NULL, sizeof(matrices_t), &s_static_renderer->matrices_uniform);
	if (!success)
	{
		fprintf(stderr, "Failed to create uniform buffer!\n");
		return false;
	}
	uniform_buffer_bind_base(&s_static_renderer->matrices_uniform, 0);

	s_static_renderer->matrices.projection = mat4_perspective(70.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	s_static_renderer->matrices.view = mat4_identity();
	s_static_renderer->matrices.view = mat4_translate_z(s_static_renderer->matrices.view, -4.0f);
	s_static_renderer->matrices.view = mat4_rotate_z(s_static_renderer->matrices.view, deg_to_rad(45.0f));
	uniform_buffer_set_data(&s_static_renderer->matrices_uniform, &s_static_renderer->matrices, sizeof(matrices_t));

	return true;
}

void static_renderer_shutdown()
{
	shader_destroy(&s_static_renderer->shader);
	s_static_renderer = NULL;
}

void static_renderer_begin_frame()
{
	shader_use(&s_static_renderer->shader);
	uniform_buffer_bind(&s_static_renderer->matrices_uniform);
	texture_bind(&s_static_renderer->texture, 0);
}

void static_renderer_end_frame()
{
}

void static_renderer_render(mesh_t* mesh)
{
	vertex_array_bind(&mesh->vertex_array);

	glDrawElements(GL_TRIANGLES, (uint32_t)mesh->index_count, GL_UNSIGNED_INT, NULL);
}

