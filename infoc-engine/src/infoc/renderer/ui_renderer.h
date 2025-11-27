#pragma once

#include "infoc/math/vec2.h"
#include "infoc/math/vec4.h"

/**
 * Enumeration for ui component placement
 */
typedef enum item_placement
{
	/** Place the item at the left/top side */
	item_placement_beg,
	/** Place the item in the center */
	item_placement_center,
	/** Place the item at the right/bottom side */
	item_placement_end
} item_placement;

/**
 * Two component unsigned int vector
 */
typedef struct uvec2
{
	/** X and Y coordinates */
	uint32_t x, y;
} uvec2;

/**
 * Information about a rendered ui component
 */
typedef struct item_info
{
	/** Position */
	uvec2 positon;
	/** Dimensions */
	uvec2 size;
	/** Is it hovered */
	bool hovered;
} item_info;

/**
 * Draws a text onto the screen
 * 
 * @param text The text to be drawn
 * @param placement_horiz The anchor point on the horizontal axis (left, center, right)
 * @param placement_vert The anchor point on the vertical axis (top, center, bottom)
 * @param x, y X and Y offset of the text
 * @param big_text A boolean indicating if the text should be drawn in big
 * 
 * @returns Information about the rendererd text
 */
item_info ui_draw_text(const char* text, item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y, bool big_text);
/**
 * Draws a button onto the screen
 *
 * @param text The label of the button
 * @param width, height The dimensions of the button
 * @param placement_horiz The anchor point on the horizontal axis (left, center, right)
 * @param placement_vert The anchor point on the vertical axis (top, center, bottom)
 * @param x, y X and Y offset of the button
 * @param colour_normal The normal colour of the button
 * @param colour_hovered The colour when hovered
 *
 * @returns Information about the rendererd button
 */
item_info ui_draw_button(const char* text, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered);
/**
 * Draws a text field onto the screen
 *
 * @param buffer A buffer with the text field contents
 * @param width, height The dimensions of the text field
 * @param placement_horiz The anchor point on the horizontal axis (left, center, right)
 * @param placement_vert The anchor point on the vertical axis (top, center, bottom)
 * @param x, y X and Y offset of the text field
 * @param background_colour The background colour of the text field
 * @param cursor A boolean indicating whether the cursor should be drawn
 *
 * @returns Information about the rendererd text field
 */
item_info ui_draw_text_field(char* buffer, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 background_colour, bool cursor);
/**
 * Draws a number spinner onto the screen
 *
 * @param number A pointer to the value
 * @param min_bounds, max_bounds The minimum and maximum value the number can be
 * @param width, height The dimensions of the spinner
 * @param placement_horiz The anchor point on the horizontal axis (left, center, right)
 * @param placement_vert The anchor point on the vertical axis (top, center, bottom)
 * @param x, y X and Y offset of the spinner
 * @param colour_normal The normal colour of the button
 * @param colour_hovered The colour when hovered
 *
 * @returns Information about the rendererd spinner
 */
item_info ui_draw_spinner(uint32_t* number, uint32_t min_bounds, uint32_t max_bounds, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered);
/**
 * Draws a checkbox onto the screen
 *
 * @param checked A pointer to a boolean indicating if the checkbox is checked
 * @param width, height The dimensions of the checkbox
 * @param placement_horiz The anchor point on the horizontal axis (left, center, right)
 * @param placement_vert The anchor point on the vertical axis (top, center, bottom)
 * @param x, y X and Y offset of the checkbox
 * @param colour_normal The normal colour of the button
 * @param colour_hovered The colour when hovered
 *
 * @returns Information about the rendererd checkbox
 */
item_info ui_draw_checkbox(bool* checked, uint32_t width, uint32_t height,
	item_placement placement_horiz, item_placement placement_vert, int32_t x, int32_t y,
	vec4 colour_normal, vec4 colour_hovered);
