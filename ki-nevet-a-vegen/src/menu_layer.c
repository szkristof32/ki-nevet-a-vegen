#include "menu_layer.h"

#include "game.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include "infoc/renderer/sdl_renderer.h"
#include "infoc/renderer/ui_renderer.h"

static void menu_on_ui_render(SDL_Renderer* renderer);
static void menu_on_window_resize(uint32_t width, uint32_t height);

typedef struct menu_layer_t
{
	layer_t* game_layer;
	uint32_t window_width, window_height;
} menu_layer_t;

static layer_t s_layer = { 0 };
static menu_layer_t* s_menu_layer = NULL;

layer_t menu_layer_create(layer_t* game_layer)
{
	arena_allocator_t* allocator = engine_get_allocator();

	s_layer.on_ui_render = menu_on_ui_render;
	s_layer.on_window_resize = menu_on_window_resize;
	s_layer.internal_state = arena_allocator_allocate(allocator, sizeof(menu_layer_t));

	s_menu_layer = (menu_layer_t*)s_layer.internal_state;
	s_menu_layer->game_layer = game_layer;

	return s_layer;
}

const float ui_padding = 15.0f;

void menu_on_ui_render(SDL_Renderer* renderer)
{
	float mouse_x = input_get_mouse_x() * s_menu_layer->window_width;
	float mouse_y = input_get_mouse_y() * s_menu_layer->window_height;

	sdl_renderer_draw_square(0, 0, (float)s_menu_layer->window_width, (float)s_menu_layer->window_height, vec4_create(0.2f, 0.2f, 0.2f, 1.0f));

	float y = 85.0f;

	item_info title = ui_draw_text(u8"Mensch ärgere Dich nicht", item_placement_center, item_placement_beg, 0.0f, y, true);
	y += title.size.y + 170.0f;

	item_info new_game_button = ui_draw_button("New game", 250.0f, 50.0f,
		item_placement_center, item_placement_beg, 0.0f, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += new_game_button.size.y + ui_padding;
	if (new_game_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		engine_detach_layer(&s_layer);
		engine_attach_layer(s_menu_layer->game_layer);
	}

	item_info exit_button = ui_draw_button("Exit", 250.0f, 50.0f,
		item_placement_center, item_placement_beg, 0.0f, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += exit_button.size.y + ui_padding;
	if (exit_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		engine_request_close();
	}
}

void menu_on_window_resize(uint32_t width, uint32_t height)
{
	s_menu_layer->window_width = width;
	s_menu_layer->window_height = height;
}
