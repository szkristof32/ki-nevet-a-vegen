#include "menu_layer.h"

#include "game.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"
#include "infoc/core/darray.h"

#include "infoc/renderer/sdl_renderer.h"
#include "infoc/renderer/ui_renderer.h"

#include "infoc/utils/file_utils.h"

#include "menu/menu_state.h"
#include "menu/main_menu.h"
#include "menu/new_game_menu.h"

#include "game_layer.h"

static void menu_on_detach();
static void menu_on_ui_render(SDL_Renderer* renderer);
static void menu_on_window_resize(uint32_t width, uint32_t height);

typedef struct menu_layer_t
{
	layer_t* game_layer;
	uint32_t window_width, window_height;

	menu_state state;
	void* state_data;
} menu_layer_t;

static layer_t s_layer = { 0 };
static menu_layer_t* s_menu_layer = NULL;

layer_t menu_layer_create(layer_t* game_layer)
{
	arena_allocator_t* allocator = engine_get_allocator();

	s_layer.on_detach = menu_on_detach;
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
static menu_state _menu_load_game();
static void _menu_exit();

void menu_on_detach()
{
	switch (s_menu_layer->state)
	{
		case menu_state_new_game_menu: new_game_menu_detach(s_menu_layer->state_data); break;
	}
	free(s_menu_layer->state_data);
}

void menu_on_ui_render(SDL_Renderer* renderer)
{
	float mouse_x = input_get_mouse_x() * s_menu_layer->window_width;
	float mouse_y = input_get_mouse_y() * s_menu_layer->window_height;

	sdl_renderer_draw_square(0, 0, (float)s_menu_layer->window_width, (float)s_menu_layer->window_height, vec4_create(0.2f, 0.2f, 0.2f, 1.0f));

	menu_state new_state = s_menu_layer->state;

	switch (s_menu_layer->state)
	{
		case menu_state_main_menu:		new_state = draw_main_menu(s_menu_layer->window_width, s_menu_layer->window_height); break;
		case menu_state_new_game_menu:	new_state = draw_new_game_menu(s_menu_layer->window_width, s_menu_layer->window_height, s_menu_layer->state_data); break;
		case menu_state_new_game:		_menu_transition_to_game(); break;
		case menu_state_load_game:		new_state = _menu_load_game(); break;
		case menu_state_exit:			_menu_exit(); break;
	}

	if (new_state != s_menu_layer->state)
	{
		if (s_menu_layer->state == menu_state_new_game_menu && new_state == menu_state_main_menu)
		{
			new_game_menu_detach(s_menu_layer->state_data);
			free(s_menu_layer->state_data);
		}

		switch (new_state)
		{
			case menu_state_new_game_menu:	s_menu_layer->state_data = new_game_menu_attach(); break;
		}
	}

	s_menu_layer->state = new_state;
}

void _menu_transition_to_game()
{
	game_configuration_t config = *(game_configuration_t*)s_menu_layer->state_data;
	engine_detach_layer(&s_layer);
	engine_attach_layer(s_menu_layer->game_layer);
	game_configure(&config);
}

static char* _get_last_game_played();

menu_state _menu_load_game()
{
	char* last_game = _get_last_game_played();
	if (!last_game)
	{
		return menu_state_main_menu;
	}
	if (!file_utils_file_exists(last_game))
	{
		free(last_game);
		return menu_state_main_menu;
	}

	game_save_t save = { 0 };
	char* save_game = file_utils_read_file(last_game);

	char* next_token = NULL;
	char* line = strtok_s(save_game, "\n", &next_token);
	size_t line_length = strlen(line);
	save.configuration.game_name = (char*)malloc(line_length * sizeof(char));
	sscanf_s(line, "nev: %s", save.configuration.game_name, (uint32_t)line_length);

	line = strtok_s(NULL, "\n", &next_token);
	sscanf_s(line, "kocka: %dd%d", &save.configuration.dice.dice_count, &save.configuration.dice.sides);

	line = strtok_s(NULL, "\n", &next_token);
	char players[4] = { 0 };
	sscanf_s(line, "jatekosok: %c,%c,%c,%c", &players[0], 1, &players[1], 1, &players[2], 1, &players[3], 1);
	for (uint32_t i = 0; i < 4; i++)
		save.configuration.players[i] = players[i] == 'h' ? player_human : player_computer;

	line = strtok_s(NULL, "\n", &next_token);
	line = strtok_s(NULL, "\n", &next_token);

	save.moves = darray_create(move_t);

	while (line)
	{
		move_t move = { 0 };
		sscanf_s(line, "%d: %d %d", (uint32_t*)&move.player, &move.move_count, &move.object);
		darray_push(save.moves, move);
		line = strtok_s(NULL, "\n", &next_token);
	}

	engine_detach_layer(&s_layer);
	engine_attach_layer(s_menu_layer->game_layer);
	game_load(&save);

	darray_destroy(save.moves);
	free(save_game);
	free(last_game);

	return menu_state_load_game;
}

char* _get_last_game_played()
{
	return file_utils_read_file("saves/last_game.dat");
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
