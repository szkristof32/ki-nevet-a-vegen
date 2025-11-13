#include "ui_renderer.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include "sdl_renderer.h"

#include <stdlib.h>

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

	width = max(text_width, width);
	height = max(text_height, height);

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

vec2 _ui_get_position(float width, float height, item_placement placement_horiz, item_placement placement_vert, float x, float y)
{
	window_t* window = engine_get_window();

	if (placement_horiz == item_placement_center)
		x = (window->width - width) / 2.0f;
	else if (placement_horiz == item_placement_end)
		x = window->width - width - x;
	if (placement_vert == item_placement_center)
		y = (window->height - height) / 2.0f;
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
