#include "game_layer.h"

#include "infoc/core/engine.h"

#include "infoc/renderer/buffers.h"
#include "infoc/renderer/vertex_array.h"
#include "infoc/renderer/shader.h"

// TODO: maybe should be abstracted away
#include "infoc/renderer/gl.h"

static void game_on_attach();
static void game_on_update(float timestep);

typedef struct game_layer_t
{
	vertex_array_t vertex_array;
	vertex_buffer_t vertex_buffer;
	shader_t shader;
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

	vertex_array_create(&s_game_layer->vertex_array);
	vertex_array_bind(&s_game_layer->vertex_array);

	vertex_buffer_create(data, sizeof(data), &s_game_layer->vertex_buffer);
	vertex_buffer_bind(&s_game_layer->vertex_buffer);

	vertex_array_add_attribute(&s_game_layer->vertex_array, vertex_attribute_type_float3);
	vertex_array_bake_layout(&s_game_layer->vertex_array);

	shader_create("assets/shaders/basic_shader.vert", "assets/shaders/basic_shader.frag", &s_game_layer->shader);
}

void game_on_update(float timestep)
{
	shader_use(&s_game_layer->shader);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
