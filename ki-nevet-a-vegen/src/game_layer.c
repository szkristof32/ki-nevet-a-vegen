#include "game_layer.h"

#include "infoc/core/engine.h"
#include "infoc/core/darray.h"
#include "infoc/core/input.h"

#include "infoc/renderer/model.h"
#include "infoc/renderer/framebuffer.h"
#include "infoc/renderer/static_renderer.h"

#include "infoc/scene/scene.h"

#include "infoc/utils/obj_loader.h"

#include "camera_controller.h"
#include "board.h"
#include "game_state.h"

#include "infoc/renderer/gl.h"
#include <SDL3/SDL_render.h>

#undef bool

static void game_on_attach();
static void game_on_detach();
static void game_on_update(float timestep);
static void game_on_ui_render(SDL_Renderer* renderer);
static void game_on_window_resize(uint32_t width, uint32_t height);

typedef struct game_layer_t
{
	framebuffer_t framebuffer;
	scene_t scene;
	camera_controller_t camera_controller;
	uint32_t hovered_object;
	uint32_t window_width, window_height;

	game_state_t game_state;
} game_layer_t;

static game_layer_t* s_game_layer = NULL;

layer_t game_layer_create()
{
	arena_allocator_t* allocator = engine_get_allocator();

	layer_t game_layer = { 0 };
	game_layer.on_attach = game_on_attach;
	game_layer.on_detach = game_on_detach;
	game_layer.on_update = game_on_update;
	game_layer.on_ui_render = game_on_ui_render;
	game_layer.on_window_resize = game_on_window_resize;
	game_layer.internal_state = arena_allocator_allocate(allocator, sizeof(game_layer_t));

	s_game_layer = (game_layer_t*)game_layer.internal_state;

	return game_layer;
}

static void _game_create_framebuffer(uint32_t width, uint32_t height);

void game_on_attach()
{
	_game_create_framebuffer(1280, 720);
	s_game_layer->window_width = 1280;
	s_game_layer->window_height = 720;

	scene_create(&s_game_layer->scene);

	camera_controller_t* controller = &s_game_layer->camera_controller;

	controller->camera = &s_game_layer->scene.camera;
	controller->pitch = 30.0f;
	controller->distance_from_center = 7.0f;

	game_state_create(&s_game_layer->scene, &s_game_layer->game_state);
}

void game_on_detach()
{
	game_state_destroy(&s_game_layer->game_state);
	scene_destroy(&s_game_layer->scene);
	framebuffer_destroy(&s_game_layer->framebuffer);
}

void game_on_update(float timestep)
{
	// GAME UPDATE
	camera_controller_update(&s_game_layer->camera_controller);
	static_renderer_set_camera(&s_game_layer->scene.camera);
	
	game_state_update(&s_game_layer->game_state, s_game_layer->hovered_object);

	// RENDER
	framebuffer_bind(&s_game_layer->framebuffer);

	for (uint32_t i = 0; i < darray_count(s_game_layer->scene.game_objects); i++)
	{
		game_object_t* object = &s_game_layer->scene.game_objects[i];

		vec4 highlight = vec4_scalar(0.0f);
		if (i != 0 && i == s_game_layer->hovered_object)
			highlight = vec4_scalar(0.2f);

		static_renderer_render(&object->model, transform_get_model_matrix(&object->transform), object->colour, object->index, highlight);
	}

	framebuffer_unbind(&s_game_layer->framebuffer);
	framebuffer_blit_to_screen(&s_game_layer->framebuffer, s_game_layer->window_width, s_game_layer->window_height);

	uint32_t x_pos = (uint32_t)(1280.0f * input_get_mouse_x());
	uint32_t y_pos = 720 - (uint32_t)(720.0f * input_get_mouse_y());
	uint32_t hovered_object_index = texture_read_pixel_uint(&s_game_layer->framebuffer.colour_attachments[1], x_pos, y_pos);

	s_game_layer->hovered_object = hovered_object_index;
}

void game_on_ui_render(SDL_Renderer* renderer)
{
	game_state_render_ui(&s_game_layer->game_state, renderer);
}

void game_on_window_resize(uint32_t width, uint32_t height)
{
	s_game_layer->window_width = width;
	s_game_layer->window_height = height;

	framebuffer_destroy(&s_game_layer->framebuffer);

	_game_create_framebuffer(width, height);
}

void _game_create_framebuffer(uint32_t width, uint32_t height)
{
	framebuffer_create(width, height, &s_game_layer->framebuffer);
	framebuffer_add_colour_attachment(&s_game_layer->framebuffer);
	framebuffer_add_attachment(&s_game_layer->framebuffer, GL_R32UI);
	framebuffer_create_depth_attachment(&s_game_layer->framebuffer);
}
