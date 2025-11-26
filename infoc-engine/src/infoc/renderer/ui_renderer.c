#include "ui_renderer.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include "sdl_renderer.h"

#include <stdlib.h>
#include <math.h>

static bool s_adjust_for_text_size = true;

static uvec2 _ui_get_position(uint32_t width, uint32_t height, item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y);
static bool _ui_is_hovered(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

item_info ui_draw_text(const char* text, item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y, bool big_text)
{
	uint32_t text_width, text_height;
	sdl_renderer_get_text_size(text, &text_width, &text_height, big_text);

	uvec2 position = _ui_get_position(text_width, text_height, placement_horiz, placement_vert, x, y);

	sdl_renderer_draw_text(text, position.x, position.y, big_text);

	bool hovered = _ui_is_hovered(x, y, text_width, text_height);

	item_info info = { 0 };
	info.positon = (uvec2){ .x = x, .y = y };
	info.size = (uvec2){ .x = text_width, .y = text_height };
	info.hovered = hovered;

	return info;
}

item_info ui_draw_button(const char* text, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered)
{
	uint32_t text_width, text_height;
	sdl_renderer_get_text_size(text, &text_width, &text_height, false);

	width = s_adjust_for_text_size ? max(text_width, width) : width;
	height = s_adjust_for_text_size ? max(text_height, height) : height;

	uvec2 pos = _ui_get_position(width, height, placement_horiz, placement_vert, x, y);
	x = pos.x;
	y = pos.y;

	bool hovered = _ui_is_hovered(x, y, width, height);
	vec4 colour = !hovered ? colour_normal : colour_hovered;

	sdl_renderer_draw_square(x, y, width, height, colour);

	sdl_renderer_draw_text(text, x + (width - text_width) / 2, y + (height - text_height) / 2, false);

	item_info info = { 0 };
	info.positon = (uvec2){ .x = x, .y = y };
	info.size = (uvec2){ .x = width, .y = height };
	info.hovered = hovered;

	return info;
}

item_info ui_draw_text_field(char* buffer, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 background_colour, bool cursor)
{
	window_t* window = engine_get_window();

	uint32_t text_width, text_height;
	sdl_renderer_get_text_size(buffer, &text_width, &text_height, false);

	width = s_adjust_for_text_size ? max(text_width, width) : width;
	height = s_adjust_for_text_size ? max(text_height, height) : height;

	uvec2 pos = _ui_get_position(width, height, placement_horiz, placement_vert, x, y);
	x = pos.x;
	y = pos.y;

	bool hovered = _ui_is_hovered(x, y, width, height);

	sdl_renderer_draw_square(x, y, width, height, background_colour);

	sdl_renderer_draw_text(buffer, x + (width - text_width) / 2, y + (height - text_height) / 2, false);
	if (cursor)
		sdl_renderer_draw_square(x + (width + text_width) / 2, y + (height - text_height) / 2, 2, text_height, vec4_scalar(1.0f));

	if (hovered && input_is_mouse_button_released(mouse_button_left))
	{
		window_start_text_input(window);
	}
	else if (!hovered && input_is_mouse_button_released(mouse_button_left))
	{
		window_stop_text_input(window);
	}

	item_info info = { 0 };
	info.positon = (uvec2){ .x = x, .y = y };
	info.size = (uvec2){ .x = width, .y = height };
	info.hovered = hovered;

	return info;
}

item_info ui_draw_spinner(uint32_t* number, uint32_t min_bounds, uint32_t max_bounds, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered)
{
	char number_text[16] = { 0 };
	sprintf_s(number_text, sizeof(number_text), "%d", *number);
	uint32_t text_width, text_height;
	sdl_renderer_get_text_size(number_text, &text_width, &text_height, false);

	width = s_adjust_for_text_size ? max(text_width, width) : width;
	height = s_adjust_for_text_size ? max(text_height, height) : height;

	uvec2 pos = _ui_get_position(width, height, placement_horiz, placement_vert, x, y);
	x = pos.x;
	y = pos.y;

	bool hovered = _ui_is_hovered(x, y, width, height);

	sdl_renderer_draw_square(x, y, width, height, colour_normal);

	sdl_renderer_draw_text(number_text, x + (width - text_width) / 2, y + (height - text_height) / 2, false);

	s_adjust_for_text_size = false;
	uint32_t control_size = min(width, height) / 2;
	item_info increase = ui_draw_button("+", control_size, control_size,
		item_placement_beg, item_placement_beg, x + width - control_size, y,
		colour_normal, colour_hovered);
	item_info decrease = ui_draw_button("-", control_size, control_size,
		item_placement_beg, item_placement_beg, x + width - control_size, y + control_size,
		colour_normal, colour_hovered);
	if (input_is_mouse_button_released(mouse_button_left))
	{
		if (increase.hovered)
			*number = min(*number + 1, max_bounds);
		else if (decrease.hovered)
			*number = max(*number - 1, min_bounds);
	}
	s_adjust_for_text_size = true;

	item_info info = { 0 };
	info.positon = (uvec2){ .x = x, .y = y };
	info.size = (uvec2){ .x = width, .y = height };
	info.hovered = hovered;

	return info;
}

item_info ui_draw_checkbox(bool* checked, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered)
{
	uvec2 pos = _ui_get_position(width, height, placement_horiz, placement_vert, x, y);
	x = pos.x;
	y = pos.y;

	bool hovered = _ui_is_hovered(x, y, width, height);

	sdl_renderer_draw_square(x, y, width, height, colour_normal);

	uint32_t dot_size = (uint32_t)ceil(min(width, height) * 0.65f);
	if (*checked)
	{
		sdl_renderer_draw_square(x + (width - dot_size) / 2, y + (height - dot_size) / 2,
			dot_size, dot_size, vec4_sub(colour_normal, vec4_scalar(0.2f)));
	}
	if (hovered && input_is_mouse_button_released(mouse_button_left))
	{
		*checked = !(*checked);
	}

	item_info info = { 0 };
	info.positon = (uvec2){ .x = x, .y = y };
	info.size = (uvec2){ .x = width, .y = height };
	info.hovered = hovered;

	return info;
}

uvec2 _ui_get_position(uint32_t width, uint32_t height, item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y)
{
	window_t* window = engine_get_window();

	if (placement_horiz == item_placement_center)
		x = (window->width - width) / 2 + x;
	else if (placement_horiz == item_placement_end)
		x = window->width - width - x;
	if (placement_vert == item_placement_center)
		y = (window->height - height) / 2 + y;
	else if (placement_vert == item_placement_end)
		y = window->height - height - y;

	return (uvec2) { .x = x, .y = y };
}

bool _ui_is_hovered(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	window_t* window = engine_get_window();

	uint32_t mouse_x = (uint32_t)(input_get_mouse_x() * (float)window->width);
	uint32_t mouse_y = (uint32_t)(input_get_mouse_y() * (float)window->height);

	return mouse_x >= x && mouse_x <= x + width && mouse_y >= y && mouse_y <= y + height;
}
