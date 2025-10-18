#include "game_layer.h"

#include "infoc/core/engine.h"

#include "infoc/renderer/mesh.h"
#include "infoc/renderer/static_renderer.h"

static void game_on_attach();
static void game_on_update(float timestep);

typedef struct game_layer_t
{
	mesh_t test_mesh;
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
	vec3 positions[] = {
		vec3_create(-0.5f, 0.5f, 0.0f),
		vec3_create(-0.5f, -0.5f, 0.0f),
		vec3_create(0.5f, 0.5f, 0.0f),
		vec3_create(0.5f, 0.5f, 0.0f),
		vec3_create(-0.5f, -0.5f, 0.0f),
		vec3_create(0.5f, -0.5f, 0.0f)
	};
	vec2 uvs[] = {
		vec2_create(0.0f, 0.0f),
		vec2_create(0.0f, 1.0f),
		vec2_create(1.0f, 0.0f),
		vec2_create(1.0f, 0.0f),
		vec2_create(0.0f, 1.0f),
		vec2_create(1.0f, 1.0f)
	};
	vec3 normals[] = {
		vec3_create(0.0f, 0.0f, 1.0f),
		vec3_create(0.0f, 0.0f, 1.0f),
		vec3_create(0.0f, 0.0f, 1.0f),
		vec3_create(0.0f, 0.0f, 1.0f),
		vec3_create(0.0f, 0.0f, 1.0f),
		vec3_create(0.0f, 0.0f, 1.0f)
	};
	vec4 colours[] = {
		vec4_create(1.0f, 0.0f, 0.0f, 1.0f),
		vec4_create(0.0f, 1.0f, 0.0f, 1.0f),
		vec4_create(0.0f, 0.0f, 1.0f, 1.0f),
		vec4_create(0.0f, 0.0f, 1.0f, 1.0f),
		vec4_create(0.0f, 1.0f, 0.0f, 1.0f),
		vec4_create(1.0f, 0.0f, 1.0f, 1.0f)
	};

	for (uint32_t i = 0; i < 6; i++)
	{
		vertex_t vertex = { 0 };
		vertex.position = positions[i];
		vertex.uv = uvs[i];
		vertex.normal = normals[i];
		vertex.colour = colours[i];

		mesh_add_vertex(&s_game_layer->test_mesh, &vertex);
	}
	mesh_create(&s_game_layer->test_mesh);
}

void game_on_update(float timestep)
{
	static_renderer_render(&s_game_layer->test_mesh);
}
