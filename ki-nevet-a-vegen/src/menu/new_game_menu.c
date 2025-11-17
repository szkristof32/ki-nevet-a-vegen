#include "new_game_menu.h"

#include "infoc/core/darray.h"
#include "infoc/core/input.h"

#include "infoc/renderer/ui_renderer.h"

#include "game_layer.h"
#include "dice.h"

extern const float ui_padding;

static char buffer[1024] = { 0 };
static dice_t dice = { .dice_count = 1, .sides = 6 };
static bool red_human = true, blue_human = true, green_human = true, yellow_human = true;

menu_state draw_new_game_menu(uint32_t window_width, uint32_t window_height)
{
	menu_state new_state = menu_state_new_game_menu;

	float mouse_x = input_get_mouse_x() * window_width;
	float mouse_y = input_get_mouse_y() * window_height;

	float y = 85.0f;

	item_info title = ui_draw_text("New game", item_placement_center, item_placement_beg, 0.0f, y, true);
	y += title.size.y + 170.0f;

	item_info new_game_button = ui_draw_button("Back", 150.0f, 50.0f,
		item_placement_beg, item_placement_beg, ui_padding, ui_padding,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	if (new_game_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_main_menu;
	}

	item_info game_name_field = ui_draw_text_field(buffer, 250.0f, 50.0f,
		item_placement_center, item_placement_beg, 0.0f, y,
		vec4_create(0.82f, 0.69f, 0.49f, 1.0f), true);
	ui_draw_text("Game name", item_placement_center, item_placement_beg, -game_name_field.size.x + 50.0f, y + 10.0f, false);
	y += game_name_field.size.y + ui_padding;
	if (input_is_key_pressed(SDLK_BACKSPACE))
	{
		size_t length = strlen(buffer);
		buffer[length - 1] = '\0';
	}
	strcat(buffer, input_get_keys_typed());

	item_info dice_count = ui_draw_spinner(&dice.dice_count, 1, 4, 117.5f, 50.0f,
		item_placement_center, item_placement_beg, -67.5f, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	item_info dice_sides = ui_draw_spinner(&dice.sides, 4, 20, 117.5f, 50.0f,
		item_placement_center, item_placement_beg, 67.5f, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	ui_draw_text("Dice", item_placement_center, item_placement_beg, -game_name_field.size.x + 90.0f, y + 10.0f, false);
	y += dice_sides.size.y + ui_padding;
	(void)dice_count;

	item_info red_player = ui_draw_checkbox(&red_human, 50.0f, 50.0f,
		item_placement_center, item_placement_beg, -100.0f, y,
		vec4_create(0.87f, 0.24f, 0.14f, 1.0f), vec4_create(0.92f, 0.29f, 0.19f, 1.0f));
	item_info blue_player = ui_draw_checkbox(&blue_human, 50.0f, 50.0f,
		item_placement_center, item_placement_beg, -32.5f, y,
		vec4_create(0.37f, 0.34f, 0.54f, 1.0f), vec4_create(0.42f, 0.39f, 0.59f, 1.0f));
	item_info green_player = ui_draw_checkbox(&green_human, 50.0f, 50.0f,
		item_placement_center, item_placement_beg, 32.5f, y,
		vec4_create(0.47f, 0.74f, 0.14f, 1.0f), vec4_create(0.52f, 0.79f, 0.19f, 1.0f));
	item_info yellow_player = ui_draw_checkbox(&yellow_human, 50.0f, 50.0f,
		item_placement_center, item_placement_beg, 100.0f, y,
		vec4_create(0.87f, 0.74f, 0.14f, 1.0f), vec4_create(0.92f, 0.79f, 0.19f, 1.0f));
	ui_draw_text("Human/AI players", item_placement_center, item_placement_beg, -game_name_field.size.x + 20.0f, y + 10.0f, false);
	y += yellow_player.size.y + ui_padding;
	(void)red_player;
	(void)blue_player;
	(void)green_player;

	item_info exit_button = ui_draw_button("Create", 250.0f, 50.0f,
		item_placement_center, item_placement_beg, 0.0f, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += exit_button.size.y + ui_padding;
	if (exit_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		size_t length = strlen(buffer) + 1;
		if (length == 1)
			return new_state;

		char* game_name = (char*)malloc(length * sizeof(char));
		sprintf_s(game_name, length, "%s", buffer);
		game_layer_set_game_name(game_name);
		game_layer_set_dice(dice);
		new_state = menu_state_game;
	}

	return new_state;
}
