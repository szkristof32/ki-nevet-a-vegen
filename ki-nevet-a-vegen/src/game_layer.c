#include "game_layer.h"

#include "infoc/core/engine.h"
#include "infoc/core/darray.h"

#include "infoc/renderer/model.h"
#include "infoc/renderer/static_renderer.h"

#include "infoc/scene/scene.h"

#include "infoc/utils/obj_loader.h"

static void game_on_attach();
static void game_on_detach();
static void game_on_update(float timestep);

typedef struct game_layer_t
{
	scene_t scene;
} game_layer_t;

static game_layer_t* s_game_layer = NULL;

layer_t game_layer_create()
{
	arena_allocator_t* allocator = engine_get_allocator();

	layer_t game_layer = { 0 };
	game_layer.on_attach = game_on_attach;
	game_layer.on_detach = game_on_detach;
	game_layer.on_update = game_on_update;
	game_layer.internal_state = arena_allocator_allocate(allocator, sizeof(game_layer_t));

	s_game_layer = (game_layer_t*)game_layer.internal_state;

	return game_layer;
}

void game_on_attach()
{
	scene_create(&s_game_layer->scene);

	{
		game_object_t* object = scene_new_object(&s_game_layer->scene);
		obj_loader_load_model("assets/models/pin_placeholder.obj", &object->model.mesh);
		texture_create("assets/images/test.bmp", &object->model.model_texture);

		object->transform.rotation.z = 13.0f;
	}
	{
		camera_t* camera = &s_game_layer->scene.camera;
		camera->transform.position = vec3_create(2.0f, 2.0f, 8.0f);
		camera->transform.rotation = vec3_create(-5.0f, 10.0f, 0.0f);
	}
}

void game_on_detach()
{
	scene_destroy(&s_game_layer->scene);
}

void game_on_update(float timestep)
{
	static_renderer_set_camera(&s_game_layer->scene.camera);

	for (uint32_t i = 0; i < darray_count(s_game_layer->scene.game_objects); i++)
	{
		game_object_t* object = &s_game_layer->scene.game_objects[i];
		static_renderer_render(&object->model, transform_get_model_matrix(&object->transform), object->colour);
	}
}
