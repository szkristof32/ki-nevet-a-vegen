#include "continue_menu.h"

#include "infoc/core/darray.h"
#include "infoc/core/input.h"

#include "infoc/renderer/ui_renderer.h"

#include "infoc/utils/file_utils.h"

extern const float ui_padding;

typedef struct continue_menu_t
{
	char* selected_game;
	char** games; // darray
} continue_menu_t;

void* continue_menu_attach()
{
	continue_menu_t* menu_data = (continue_menu_t*)malloc(sizeof(continue_menu_t));
	if (!menu_data)
		return NULL;
	menu_data->selected_game = NULL;
	menu_data->games = file_utils_get_files_in_directory("saves");

	return menu_data;
}

void continue_menu_detach(void* menu_data_ext)
{
	continue_menu_t* menu_data = (continue_menu_t*)menu_data_ext;

	for (uint32_t i = 0; i < darray_count(menu_data->games); i++)
		free(menu_data->games[i]);
	darray_destroy(menu_data->games);

	if (menu_data->selected_game)
		free(menu_data->selected_game);
}

menu_state draw_continue_menu(uint32_t window_width, uint32_t window_height, void* menu_data_ext)
{
	menu_state new_state = menu_state_continue_menu;
	continue_menu_t* menu_data = (continue_menu_t*)menu_data_ext;

	float mouse_x = input_get_mouse_x() * window_width;
	float mouse_y = input_get_mouse_y() * window_height;

	float y = 85.0f;

	item_info title = ui_draw_text("Continue", item_placement_center, item_placement_beg, 0.0f, y, true);
	y += title.size.y + 170.0f;

	item_info new_game_button = ui_draw_button("Back", 150.0f, 50.0f,
		item_placement_beg, item_placement_beg, ui_padding, ui_padding,
		vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
	if (new_game_button.hovered && input_is_mouse_button_released(mouse_button_left))
	{
		new_state = menu_state_main_menu;
	}

	for (uint32_t i = 0; i < darray_count(menu_data->games); i++)
	{
		item_info exit_button = ui_draw_button(menu_data->games[i], 250.0f, 50.0f,
			item_placement_center, item_placement_beg, 0.0f, y,
			vec4_create(0.87f, 0.74f, 0.54f, 1.0f), vec4_create(0.92f, 0.79f, 0.59f, 1.0f));
		y += exit_button.size.y + ui_padding;
		if (exit_button.hovered && input_is_mouse_button_released(mouse_button_left))
		{
			size_t game_name_length = strlen(menu_data->games[i]);
			char* path = (char*)malloc((game_name_length + game_name_length + 7) * sizeof(char));
			sprintf_s(path, (game_name_length + 7), "saves/%s", menu_data->games[i]);
			menu_data->selected_game = path;
			new_state = menu_state_load_game;
		}
	}

	return new_state;
}
