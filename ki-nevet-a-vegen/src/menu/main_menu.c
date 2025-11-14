#include "main_menu.h"

#include "infoc/core/input.h"

#include "infoc/renderer/ui_renderer.h"

extern const float ui_padding;

menu_state draw_main_menu(uint32_t window_width, uint32_t window_height)
{
	menu_state new_state = menu_state_main_menu;

	float mouse_x = input_get_mouse_x() * window_width;
	float mouse_y = input_get_mouse_y() * window_height;

	float y = 85.0f;

	item_info title = ui_draw_text(u8"Mensch ärgere Dich nicht", item_placement_center, item_placement_beg, 0.0f, y, true);
	y += title.size.y + 170.0f;

	item_info new_game_button = ui_draw_button("New game", 250.0f, 50.0f,
		item_placement_center, item_placement_beg, 0.0f, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += new_game_button.size.y + ui_padding;
	if (new_game_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_game;
	}

	item_info exit_button = ui_draw_button("Exit", 250.0f, 50.0f,
		item_placement_center, item_placement_beg, 0.0f, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += exit_button.size.y + ui_padding;
	if (exit_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_exit;
	}

	return new_state;
}
