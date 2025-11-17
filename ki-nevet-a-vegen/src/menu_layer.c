#include "menu_layer.h"

#include "game.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include "infoc/renderer/sdl_renderer.h"
#include "infoc/renderer/ui_renderer.h"

#include "menu/menu_state.h"
#include "menu/main_menu.h"
#include "game_layer.h"

static void menu_on_ui_render(SDL_Renderer* renderer);
static void menu_on_window_resize(uint32_t width, uint32_t height);

typedef struct menu_layer_t
{
	layer_t* game_layer;
	uint32_t window_width, window_height;

	menu_state state;
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
	s_menu_layer->state = menu_state_main_menu;

	return s_layer;
}

const float ui_padding = 15.0f;

static void _menu_transition_to_game();
static void _menu_exit();

void menu_on_ui_render(SDL_Renderer* renderer)
{
	float mouse_x = input_get_mouse_x() * s_menu_layer->window_width;
	float mouse_y = input_get_mouse_y() * s_menu_layer->window_height;

	sdl_renderer_draw_square(0, 0, (float)s_menu_layer->window_width, (float)s_menu_layer->window_height, vec4_create(0.2f, 0.2f, 0.2f, 1.0f));

	switch (s_menu_layer->state)
	{
		case menu_state_main_menu:	s_menu_layer->state = draw_main_menu(s_menu_layer->window_width, s_menu_layer->window_height); break;
		case menu_state_game:		_menu_transition_to_game(); break;
		case menu_state_exit:		_menu_exit(); break;
	}
}

void _menu_transition_to_game()
{
	char* game_name = (char*)malloc(6 * sizeof(char));
	sprintf_s(game_name, 6, "game0");
	game_layer_set_game_name(game_name);

	engine_detach_layer(&s_layer);
	engine_attach_layer(s_menu_layer->game_layer);
}

void _menu_exit()
{
	engine_request_close();
}

void menu_on_window_resize(uint32_t width, uint32_t height)
{
	s_menu_layer->window_width = width;
	s_menu_layer->window_height = height;
}
