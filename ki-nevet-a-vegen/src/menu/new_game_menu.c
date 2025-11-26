#include "new_game_menu.h"

#include "infoc/core/engine.h"
#include "infoc/core/darray.h"
#include "infoc/core/input.h"

#include "infoc/renderer/ui_renderer.h"

#include "game_layer.h"
#include "dice.h"

#include <SDL_keycode.h>
#include <stdlib.h>

extern const int32_t ui_padding;

typedef struct new_game_menu_t
{
	char* buffer; // darray
	dice_t dice;
	player_type players[4];
} new_game_menu_t;

void* new_game_menu_attach()
{
	new_game_menu_t* menu_data = (new_game_menu_t*)malloc(sizeof(new_game_menu_t));
	if (!menu_data)
		return NULL;
	menu_data->buffer = darray_create(char);
	menu_data->dice = (dice_t){ .dice_count = 1, .sides = 6 };
	for (uint32_t i = 0; i < 4; i++)
		menu_data->players[i] = player_human;

	return menu_data;
}

void new_game_menu_detach(void* menu_data_ext)
{
	new_game_menu_t* menu_data = (new_game_menu_t*)menu_data_ext;
	darray_destroy(menu_data->buffer);
}

menu_state draw_new_game_menu(uint32_t window_width, uint32_t window_height, void* menu_data_ext)
{
	menu_state new_state = menu_state_new_game_menu;
	new_game_menu_t* menu_data = (new_game_menu_t*)menu_data_ext;

	uint32_t y = 85;

	item_info title = ui_draw_text("New game", item_placement_center, item_placement_beg, 0, y, true);
	y += title.size.y + 170;

	item_info new_game_button = ui_draw_button("Back", 150, 50,
		item_placement_beg, item_placement_beg, ui_padding, ui_padding,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	if (new_game_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_main_menu;
	}

	item_info game_name_field = ui_draw_text_field(menu_data->buffer, 250, 50,
		item_placement_center, item_placement_beg, 0, y,
		vec4_create(0.82f, 0.69f, 0.49f, 1.0f), true);
	ui_draw_text("Game name", item_placement_center, item_placement_beg, -(int32_t)game_name_field.size.x + 50, y + 10, false);
	y += game_name_field.size.y + ui_padding;
	if (input_is_key_pressed(SDLK_BACKSPACE))
	{
		darray_erase(menu_data->buffer, darray_count(menu_data->buffer) - 2);
	}
	char* keys_typed = input_get_keys_typed();
	if (darray_count(keys_typed) != 0)
	{
		darray_erase(menu_data->buffer, darray_count(menu_data->buffer) - 1);
		for (size_t i = 0; i < darray_count(keys_typed); i++)
			darray_push(menu_data->buffer, keys_typed[i]);
		darray_push(menu_data->buffer, '\0');
	}

	item_info dice_count = ui_draw_spinner(&menu_data->dice.dice_count, 1, 4, 117, 50,
		item_placement_center, item_placement_beg, -67, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	item_info dice_sides = ui_draw_spinner(&menu_data->dice.sides, 4, 20, 117, 50,
		item_placement_center, item_placement_beg, 67, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	ui_draw_text("Dice", item_placement_center, item_placement_beg, -(int32_t)game_name_field.size.x + 90, y + 10, false);
	y += dice_sides.size.y + ui_padding;
	(void)dice_count;

	item_info red_player = ui_draw_checkbox((bool*)&menu_data->players[0], 50, 50,
		item_placement_center, item_placement_beg, -100, y,
		vec4_create(0.87f, 0.24f, 0.14f, 1.0f), vec4_create(0.92f, 0.29f, 0.19f, 1.0f));
	item_info blue_player = ui_draw_checkbox((bool*)&menu_data->players[1], 50, 50,
		item_placement_center, item_placement_beg, -32, y,
		vec4_create(0.37f, 0.34f, 0.54f, 1.0f), vec4_create(0.42f, 0.39f, 0.59f, 1.0f));
	item_info green_player = ui_draw_checkbox((bool*)&menu_data->players[2], 50, 50,
		item_placement_center, item_placement_beg, 32, y,
		vec4_create(0.47f, 0.74f, 0.14f, 1.0f), vec4_create(0.52f, 0.79f, 0.19f, 1.0f));
	item_info yellow_player = ui_draw_checkbox((bool*)&menu_data->players[3], 50, 50,
		item_placement_center, item_placement_beg, 100, y,
		vec4_create(0.87f, 0.74f, 0.14f, 1.0f), vec4_create(0.92f, 0.79f, 0.19f, 1.0f));
	ui_draw_text("Human/AI players", item_placement_center, item_placement_beg, -(int32_t)game_name_field.size.x + 20, y + 10, false);
	y += yellow_player.size.y + ui_padding;
	(void)red_player;
	(void)blue_player;
	(void)green_player;

	item_info exit_button = ui_draw_button("Create", 250, 50,
		item_placement_center, item_placement_beg, 0, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += exit_button.size.y + ui_padding;
	if (exit_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		size_t length = strlen(menu_data->buffer) + 1;
		if (length == 1)
			return new_state;

		char* game_name = (char*)malloc(length * sizeof(char));
		memcpy(game_name, menu_data->buffer, length);
		darray_destroy(menu_data->buffer);
		menu_data->buffer = game_name;

		new_state = menu_state_new_game;
	}

	return new_state;
}
