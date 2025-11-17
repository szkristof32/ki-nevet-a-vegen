#include "ui_renderer.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include "sdl_renderer.h"

#include <stdlib.h>

static bool s_adjust_for_text_size = true;

static vec2 _ui_get_position(float width, float height, item_placement placement_horiz, item_placement placement_vert, float x, float y);
static bool _ui_is_hovered(float x, float y, float width, float height);

item_info ui_draw_text(const char* text, item_placement placement_horiz, item_placement placement_vert, float x, float y, bool big_text)
{
	float text_width, text_height;
	sdl_renderer_get_text_size(text, &text_width, &text_height, big_text);

	vec2 position = _ui_get_position(text_width, text_height, placement_horiz, placement_vert, x, y);

	sdl_renderer_draw_text(text, position.x, position.y, big_text);

	bool hovered = _ui_is_hovered(x, y, text_width, text_height);

	item_info info = { 0 };
	info.positon = vec2_create(x, y);
	info.size = vec2_create(text_width, text_height);
	info.hovered = hovered;

	return info;
}

item_info ui_draw_button(const char* text, float width, float height,
	item_placement placement_horiz, item_placement placement_vert, float x, float y,
	vec4 colour_normal, vec4 colour_hovered)
{
	window_t* window = engine_get_window();

	float text_width, text_height;
	sdl_renderer_get_text_size(text, &text_width, &text_height, false);

	width = s_adjust_for_text_size ? max(text_width, width) : width;
	height = s_adjust_for_text_size ? max(text_height, height) : height;

	vec2 pos = _ui_get_position(width, height, placement_horiz, placement_vert, x, y);
	x = pos.x;
	y = pos.y;

	bool hovered = _ui_is_hovered(x, y, width, height);
	vec4 colour = !hovered ? colour_normal : colour_hovered;

	sdl_renderer_draw_square(x, y, width, height, colour);

	sdl_renderer_draw_text(text, x + (width - text_width) / 2.0f, y + (height - text_height) / 2.0f, false);

	item_info info = { 0 };
	info.positon = vec2_create(x, y);
	info.size = vec2_create(width, height);
	info.hovered = hovered;

	return info;
}

item_info ui_draw_text_field(char* buffer, float width, float height,
	item_placement placement_horiz, item_placement placement_vert, float x, float y,
	vec4 background_colour, bool cursor)
{
	window_t* window = engine_get_window();

	float text_width, text_height;
	sdl_renderer_get_text_size(buffer, &text_width, &text_height, false);

	width = s_adjust_for_text_size ? max(text_width, width) : width;
	height = s_adjust_for_text_size ? max(text_height, height) : height;

	vec2 pos = _ui_get_position(width, height, placement_horiz, placement_vert, x, y);
	x = pos.x;
	y = pos.y;

	bool hovered = _ui_is_hovered(x, y, width, height);

	sdl_renderer_draw_square(x, y, width, height, background_colour);

	sdl_renderer_draw_text(buffer, x + (width - text_width) / 2.0f, y + (height - text_height) / 2.0f, false);
	if (cursor)
		sdl_renderer_draw_square(x + (width + text_width) / 2.0f, y + (height - text_height) / 2.0f, 2.0f, text_height, vec4_scalar(1.0f));

	if (hovered && input_is_mouse_button_clicked(mouse_button_left))
	{
		window_start_text_input(window);
	}
	else if (!hovered && input_is_mouse_button_clicked(mouse_button_left))
	{
		window_stop_text_input(window);
	}

	item_info info = { 0 };
	info.positon = vec2_create(x, y);
	info.size = vec2_create(width, height);
	info.hovered = hovered;

	return info;
}

item_info ui_draw_spinner(uint32_t* number, uint32_t min_bounds, uint32_t max_bounds, float width, float height,
	item_placement placement_horiz, item_placement placement_vert, float x, float y,
	vec4 colour_normal, vec4 colour_hovered)
{
	window_t* window = engine_get_window();

	char number_text[16] = { 0 };
	sprintf_s(number_text, sizeof(number_text), "%d", *number);
	float text_width, text_height;
	sdl_renderer_get_text_size(number_text, &text_width, &text_height, false);

	width = s_adjust_for_text_size ? max(text_width, width) : width;
	height = s_adjust_for_text_size ? max(text_height, height) : height;

	vec2 pos = _ui_get_position(width, height, placement_horiz, placement_vert, x, y);
	x = pos.x;
	y = pos.y;

	bool hovered = _ui_is_hovered(x, y, width, height);

	sdl_renderer_draw_square(x, y, width, height, colour_normal);

	sdl_renderer_draw_text(number_text, x + (width - text_width) / 2.0f, y + (height - text_height) / 2.0f, false);

	s_adjust_for_text_size = false;
	float control_size = min(width, height) / 2.0f;
	item_info increase = ui_draw_button("+", control_size, control_size,
		item_placement_beg, item_placement_beg, x + width - control_size, y,
		colour_normal, colour_hovered);
	item_info decrease = ui_draw_button("-", control_size, control_size,
		item_placement_beg, item_placement_beg, x + width - control_size, y + control_size,
		colour_normal, colour_hovered);
	if (input_is_mouse_button_clicked(mouse_button_left))
	{
		if (increase.hovered)
			*number = min(*number + 1, max_bounds);
		else if (decrease.hovered)
			*number = max(*number - 1, min_bounds);
	}
	s_adjust_for_text_size = true;

	item_info info = { 0 };
	info.positon = vec2_create(x, y);
	info.size = vec2_create(width, height);
	info.hovered = hovered;

	return info;
}

vec2 _ui_get_position(float width, float height, item_placement placement_horiz, item_placement placement_vert, float x, float y)
{
	window_t* window = engine_get_window();

	if (placement_horiz == item_placement_center)
		x = (window->width - width) / 2.0f + x;
	else if (placement_horiz == item_placement_end)
		x = window->width - width - x;
	if (placement_vert == item_placement_center)
		y = (window->height - height) / 2.0f + y;
	else if (placement_vert == item_placement_end)
		y = window->height - height - y;

	return vec2_create(x, y);
}

bool _ui_is_hovered(float x, float y, float width, float height)
{
	window_t* window = engine_get_window();

	float mouse_x = input_get_mouse_x() * window->width;
	float mouse_y = input_get_mouse_y() * window->height;

	return mouse_x >= x && mouse_x <= x + width && mouse_y >= y && mouse_y <= y + height;
}
