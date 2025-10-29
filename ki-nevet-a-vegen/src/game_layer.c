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

#include "infoc/renderer/gl.h"
#include <SDL3/SDL_render.h>

#undef bool

static void game_on_attach();
static void game_on_detach();
static void game_on_update(float timestep);
static void game_on_ui_render(SDL_Renderer* renderer);

typedef struct game_layer_t
{
	framebuffer_t framebuffer;
	scene_t scene;
	camera_controller_t camera_controller;
	board_t board;
	uint32_t highlighted_object;
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
	game_layer.internal_state = arena_allocator_allocate(allocator, sizeof(game_layer_t));

	s_game_layer = (game_layer_t*)game_layer.internal_state;

	return game_layer;
}

void game_on_attach()
{
	framebuffer_create(1280, 720, &s_game_layer->framebuffer);
	framebuffer_add_colour_attachment(&s_game_layer->framebuffer);
	framebuffer_add_colour_attachment(&s_game_layer->framebuffer);
	framebuffer_create_depth_attachment(&s_game_layer->framebuffer);

	scene_create(&s_game_layer->scene);

	camera_controller_t* controller = &s_game_layer->camera_controller;

	controller->camera = &s_game_layer->scene.camera;
	controller->pitch = 30.0f;
	controller->distance_from_center = 7.0f;

	board_create(&s_game_layer->scene, &s_game_layer->board);
}

void game_on_detach()
{
	board_destroy(&s_game_layer->board);
	scene_destroy(&s_game_layer->scene);
	framebuffer_destroy(&s_game_layer->framebuffer);
}

void game_on_update(float timestep)
{
	camera_controller_update(&s_game_layer->camera_controller);

	static_renderer_set_camera(&s_game_layer->scene.camera);
	static_renderer_set_object_count((uint32_t)darray_count(s_game_layer->scene.game_objects));

	framebuffer_bind(&s_game_layer->framebuffer);

	for (uint32_t i = 0; i < darray_count(s_game_layer->scene.game_objects); i++)
	{
		game_object_t* object = &s_game_layer->scene.game_objects[i];

		vec4 highlight = vec4_scalar(0.0f);
		if (i != 0 && i == s_game_layer->highlighted_object)
			highlight = vec4_scalar(0.2f);

		static_renderer_render(&object->model, transform_get_model_matrix(&object->transform), object->colour, object->index, highlight);
	}

	framebuffer_unbind(&s_game_layer->framebuffer);
	framebuffer_blit_to_screen(&s_game_layer->framebuffer, 1280, 720);

	uint32_t x_pos = (uint32_t)(1280.0f * input_get_mouse_x());
	uint32_t y_pos = 720 - (uint32_t)(720.0f * input_get_mouse_y());
	vec4 pixel = texture_read_pixel(&s_game_layer->framebuffer.colour_attachments[1], x_pos, y_pos);
	uint32_t hovered_object_index = (uint32_t)((float)darray_count(s_game_layer->scene.game_objects) * pixel.r);

	s_game_layer->highlighted_object = hovered_object_index;
}

void game_on_ui_render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColorFloat(renderer, 1.0f, 0.5f, 1.0f, 1.0f);
	SDL_FRect rect = { 0 };
	rect.x = 20.0f;
	rect.y = 20.0f;
	rect.w = 150.0f;
	rect.h = 50.0f;
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderScale(renderer, 2.0f, 2.0f);
	SDL_SetRenderDrawColorFloat(renderer, 1.0f, 1.0f, 1.0f, 1.0f);
	SDL_RenderDebugText(renderer, 20.0f, 20.0f, "Test");
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}
