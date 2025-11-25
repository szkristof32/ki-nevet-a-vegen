#include "static_renderer.h"

#include "infoc/core/engine.h"

#include "infoc/math/mat4.h"
#include "infoc/math/utilities.h"

#include "shader.h"
#include "gl.h"

typedef struct matrices_t
{
	mat4 projection;
	mat4 view;
} matrices_t;

typedef struct object_t
{
	mat4 transformation;
	vec4 colour;
	uint32_t index;
	vec3 _padding;
	vec4 highlight;
} object_t;

typedef struct static_renderer_t
{
	shader_t shader;

	matrices_t matrices;
	uniform_buffer_t matrices_uniform;

	uniform_buffer_t object_uniform;
} static_renderer_t;

static static_renderer_t* s_static_renderer = NULL;

static void _static_renderer_create_projection(uint32_t width, uint32_t height);

bool static_renderer_init()
{
	arena_allocator_t* allocator = engine_get_allocator();
	s_static_renderer = arena_allocator_allocate(allocator, sizeof(static_renderer_t));
	check_error(s_static_renderer == NULL, "Failed to initialise static renderer!");

	bool success = shader_create("assets/shaders/static_shader.vert", "assets/shaders/static_shader.frag", &s_static_renderer->shader);
	check_error(!success, "Failed to create static shader!");

	success = uniform_buffer_create(NULL, sizeof(matrices_t), &s_static_renderer->matrices_uniform);
	check_error(!success, "Failed to create uniform buffer!");

	uniform_buffer_bind_base(&s_static_renderer->matrices_uniform, 0);

	_static_renderer_create_projection(1280, 720);
	s_static_renderer->matrices.view = mat4_identity();
	s_static_renderer->matrices.view = mat4_translate_z(s_static_renderer->matrices.view, -10.0f);
	s_static_renderer->matrices.view = mat4_rotate_y(s_static_renderer->matrices.view, deg_to_rad(19.0f));
	s_static_renderer->matrices.view = mat4_rotate_z(s_static_renderer->matrices.view, deg_to_rad(45.0f));
	uniform_buffer_set_data(&s_static_renderer->matrices_uniform, &s_static_renderer->matrices, sizeof(matrices_t));

	success = uniform_buffer_create(NULL, sizeof(object_t), &s_static_renderer->object_uniform);
	check_error(!success, "Failed to create uniform buffer!");

	uniform_buffer_bind_base(&s_static_renderer->object_uniform, 1);

	return true;
}

void static_renderer_shutdown()
{
	shader_destroy(&s_static_renderer->shader);
	s_static_renderer = NULL;
}

void static_renderer_begin_frame()
{
	glEnable(GL_DEPTH_TEST);

	shader_use(&s_static_renderer->shader);
	uniform_buffer_bind(&s_static_renderer->matrices_uniform);
}

void static_renderer_end_frame()
{
}

void static_renderer_on_window_resize(uint32_t width, uint32_t height)
{
	_static_renderer_create_projection(width, height);
	uniform_buffer_set_data(&s_static_renderer->matrices_uniform, &s_static_renderer->matrices, sizeof(matrices_t));
}

void static_renderer_set_camera(camera_t* camera)
{
	s_static_renderer->matrices.view = camera->view_matrix;
	uniform_buffer_set_data(&s_static_renderer->matrices_uniform, &s_static_renderer->matrices, sizeof(matrices_t));
}

void static_renderer_render(model_t* model, mat4 transformation_matrix, vec4 colour, uint32_t index, vec4 highlight)
{
	object_t object_uniforms = { 0 };
	object_uniforms.transformation = transformation_matrix;
	object_uniforms.colour = colour;
	object_uniforms.index = index;
	object_uniforms.highlight = highlight;

	uniform_buffer_set_data(&s_static_renderer->object_uniform, &object_uniforms, sizeof(object_t));

	mesh_t* mesh = &model->mesh;

	vertex_array_bind(&mesh->vertex_array);
	if (texture_is_valid(&model->model_texture))
		texture_bind(&model->model_texture, 0);
	else
		texture_bind(engine_get_default_texture(), 0);

	uniform_buffer_bind(&s_static_renderer->object_uniform);

	glDrawElements(GL_TRIANGLES, (uint32_t)mesh->index_count, GL_UNSIGNED_INT, NULL);
}

void _static_renderer_create_projection(uint32_t width, uint32_t height)
{
	s_static_renderer->matrices.projection = mat4_perspective(70.0f, (float)width / (float)height, 0.1f, 1000.0f);
}
