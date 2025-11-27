#include "main_menu.h"

#include "infoc/core/input.h"

#include "infoc/renderer/ui_renderer.h"

extern const int32_t ui_padding;

menu_state draw_main_menu(uint32_t window_width, uint32_t window_height)
{
	menu_state new_state = menu_state_main_menu;

	uint32_t y = 85;

	item_info title = ui_draw_text("Mensch ärgere Dich nicht", item_placement_center, item_placement_beg, 0, y, true);
	y += title.size.y + 170;

	item_info continue_button = ui_draw_button("Continue", 250, 50,
		item_placement_center, item_placement_beg, 0, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += continue_button.size.y + ui_padding;
	if (continue_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_continue_menu;
	}

	item_info new_game_button = ui_draw_button("New game", 250, 50,
		item_placement_center, item_placement_beg, 0, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += new_game_button.size.y + ui_padding;
	if (new_game_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_new_game_menu;
	}

	item_info exit_button = ui_draw_button("Exit", 250, 50,
		item_placement_center, item_placement_beg, 0, y,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	y += exit_button.size.y + ui_padding;
	if (exit_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_exit;
	}

	return new_state;
}
