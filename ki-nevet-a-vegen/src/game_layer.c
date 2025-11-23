#include "game_layer.h"

#include "infoc/core/engine.h"
#include "infoc/core/darray.h"
#include "infoc/core/input.h"

#include "infoc/renderer/model.h"
#include "infoc/renderer/framebuffer.h"
#include "infoc/renderer/static_renderer.h"
#include "infoc/renderer/ui_renderer.h"

#include "infoc/scene/scene.h"

#include "infoc/utils/obj_loader.h"

#include "camera_controller.h"
#include "board.h"
#include "game_state.h"

#include "menu_layer.h"

#include "infoc/renderer/gl.h"
#include <SDL3/SDL_render.h>

#include <stdlib.h>

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

	game_configuration_t configuration;
	game_state_t game_state;

	bool enable_ui_input;
	bool ui_hovered;
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

void game_load(const game_save_t* save)
{
	game_configure(&save->configuration);
	for (uint32_t i = 0; i < darray_count(save->moves); i++)
	{
		game_state_play_move(&s_game_layer->game_state, &save->moves[i], false);
	}
}

void game_configure(const game_configuration_t* configuration)
{
	memcpy(&s_game_layer->configuration, configuration, sizeof(game_configuration_t));
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

	game_state_create(&s_game_layer->scene, &s_game_layer->game_state, &s_game_layer->configuration);
}

void game_on_detach()
{
	game_state_destroy(&s_game_layer->game_state);
	free(s_game_layer->configuration.game_name);
	scene_destroy(&s_game_layer->scene);
	framebuffer_destroy(&s_game_layer->framebuffer);
}

void game_on_update(float timestep)
{
	// GAME UPDATE
	camera_controller_update(&s_game_layer->camera_controller, !s_game_layer->ui_hovered);
	static_renderer_set_camera(&s_game_layer->scene.camera);

	bool enable_ui_input = !s_game_layer->camera_controller.is_moving;
	s_game_layer->enable_ui_input = s_game_layer->enable_ui_input && enable_ui_input;

	game_state_update(&s_game_layer->game_state, s_game_layer->hovered_object, timestep, s_game_layer->enable_ui_input);

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

extern float ui_padding;

void game_on_ui_render(SDL_Renderer* renderer)
{
	s_game_layer->ui_hovered = game_state_render_ui(&s_game_layer->game_state, renderer);

	item_info back_button = ui_draw_button("Back to main menu", 250.0f, 50.0f,
		item_placement_end, item_placement_beg, ui_padding, ui_padding,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	if (back_button.hovered && s_game_layer->enable_ui_input && input_is_mouse_button_released(mouse_button_left))
	{
		menu_layer_transition_to();
	}
	s_game_layer->ui_hovered |= back_button.hovered;

	item_info save_button = ui_draw_button("Manual save", 250.0f, 50.0f,
		item_placement_end, item_placement_beg, ui_padding, 2.0f * ui_padding + 50.0f,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	if (save_button.hovered && s_game_layer->enable_ui_input && input_is_mouse_button_released(mouse_button_left))
	{
		game_state_save(&s_game_layer->game_state);
	}
	s_game_layer->ui_hovered |= save_button.hovered;

	s_game_layer->enable_ui_input = !s_game_layer->camera_controller.is_moving;
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
