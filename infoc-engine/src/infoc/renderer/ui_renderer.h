#pragma once

#include "infoc/math/vec2.h"
#include "infoc/math/vec4.h"

typedef enum item_placement
{
	item_placement_beg,
	item_placement_center,
	item_placement_end
} item_placement;

typedef struct uvec2
{
	uint32_t x, y;
} uvec2;

typedef struct item_info
{
	uvec2 positon;
	uvec2 size;
	bool hovered;
} item_info;

item_info ui_draw_text(const char* text, item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y, bool big_text);
item_info ui_draw_button(const char* text, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered);
item_info ui_draw_text_field(char* buffer, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 background_colour, bool cursor);
item_info ui_draw_spinner(uint32_t* number, uint32_t min_bounds, uint32_t max_bounds, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered);
item_info ui_draw_checkbox(bool* checked, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered);
