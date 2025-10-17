#include "game_layer.h"

#include "infoc/core/engine.h"

#include "infoc/renderer/buffers.h"
#include "infoc/renderer/vertex_array.h"
#include "infoc/renderer/shader.h"

// TODO: maybe should be abstracted away
#include "infoc/renderer/gl.h"

#include "infoc/math/mat4.h"
#include "infoc/math/utilities.h"

static void game_on_attach();
static void game_on_update(float timestep);

typedef struct matrices_t
{
	mat4 projection;
	mat4 view;
} matrices_t;

typedef struct game_layer_t
{
	vertex_array_t vertex_array;
	vertex_buffer_t vertex_buffer;
	index_buffer_t index_buffer;
	shader_t shader;
	matrices_t matrices;
	uniform_buffer_t matrices_uniform;
} game_layer_t;

static game_layer_t* s_game_layer = NULL;

layer_t game_layer_create()
{
	arena_allocator_t* allocator = engine_get_allocator();

	layer_t game_layer = { 0 };
	game_layer.on_attach = game_on_attach;
	game_layer.on_update = game_on_update;
	game_layer.internal_state = arena_allocator_allocate(allocator, sizeof(game_layer_t));

	s_game_layer = (game_layer_t*)game_layer.internal_state;

	return game_layer;
}

void game_on_attach()
{
	float data[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};
	uint32_t indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	vertex_array_create(&s_game_layer->vertex_array);
	vertex_array_bind(&s_game_layer->vertex_array);

	vertex_buffer_create(data, sizeof(data), &s_game_layer->vertex_buffer);
	vertex_buffer_bind(&s_game_layer->vertex_buffer);

	index_buffer_create(indices, countof(indices), &s_game_layer->index_buffer);
	index_buffer_bind(&s_game_layer->index_buffer);

	vertex_array_add_attribute(&s_game_layer->vertex_array, vertex_attribute_type_float3);
	vertex_array_bake_layout(&s_game_layer->vertex_array);

	shader_create("assets/shaders/basic_shader.vert", "assets/shaders/basic_shader.frag", &s_game_layer->shader);

	uniform_buffer_create(NULL, sizeof(matrices_t), &s_game_layer->matrices_uniform);
	uniform_buffer_bind_base(&s_game_layer->matrices_uniform, 0);

	s_game_layer->matrices.projection = mat4_perspective(70.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	s_game_layer->matrices.view = mat4_identity();
	s_game_layer->matrices.view = mat4_translate_z(s_game_layer->matrices.view, -4.0f);
	s_game_layer->matrices.view = mat4_rotate_z(s_game_layer->matrices.view, deg_to_rad(45.0f));
	uniform_buffer_set_data(&s_game_layer->matrices_uniform, &s_game_layer->matrices, sizeof(matrices_t));
}

void game_on_update(float timestep)
{
	shader_use(&s_game_layer->shader);
	uniform_buffer_bind(&s_game_layer->matrices_uniform);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
