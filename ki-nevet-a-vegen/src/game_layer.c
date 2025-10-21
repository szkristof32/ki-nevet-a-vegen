#include "game_layer.h"

#include "infoc/core/engine.h"

#include "infoc/renderer/model.h"
#include "infoc/renderer/static_renderer.h"

#include "infoc/utils/obj_loader.h"

static void game_on_attach();
static void game_on_update(float timestep);

typedef struct game_layer_t
{
	model_t test_model;
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
	obj_loader_load_model("assets/models/pin_placeholder.obj", &s_game_layer->test_model.mesh);

	texture_create("assets/images/test.bmp", &s_game_layer->test_model.model_texture);
}

void game_on_update(float timestep)
{
	static_renderer_render(&s_game_layer->test_model);
}
