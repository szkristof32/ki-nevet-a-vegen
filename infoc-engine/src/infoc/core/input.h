#pragma once

#include "defines.h"

/*
* Mouse button codes
*/
typedef enum mouse_button
{
	mouse_button_left,		/* Left mouse button */
	mouse_button_right,		/* Right mouse button */
	mouse_button_middle		/* Middle mouse button */
} mouse_button;

/*
* Initialises the input system
*
* @returns A boolean inidicating whether the operation finished succesfully
*/
bool input_initialise();
/*
* Shuts down the input system
*/
void input_shutdown();

/*
* Updates the input system
*/
void input_update();

/*
* Mouse move listener. Should only be called by the event handler
*
* @param x The x coordinate of the mouse
* @param y The y coordinate of the mouse
*/
void input_move_listener(float x, float y);
/*
* Mouse click listener. Should only be called by the event handler
*
* @param button The button code of the mouse button
* @param pressed A boolean indicating whether the button is pressed or released
*/
void input_click_listener(uint32_t button, bool pressed);
/*
* Mouse scroll listener. Should only be called by the event handler
*
* @param scroll_x The horizontal offset of the scroll wheel
* @param scroll_y The vertical offset of the scroll wheel
*/
void input_scroll_listener(float scroll_x, float scroll_y);

/*
* Checks if mouse button is currently pressed
*
* @param button The button code of the mouse button
*
* @returns A boolean indicating whether the button is currently pressed
*/
bool input_is_mouse_button_down(uint32_t button);
/*
* Checks if mouse button is clicked this frame
*
* @param button The button code of the mouse button
*
* @returns A boolean indicating whether the button is clicked
*/
bool input_is_mouse_button_clicked(uint32_t button);
/*
* Checks if mouse button is released this frame
*
* @param button The button code of the mouse button
*
* @returns A boolean indicating whether the button is released
*/
bool input_is_mouse_button_released(uint32_t button);

/*
* Gets the mouse x coordinate
*
* @returns The x coordinate of mouse
*/
float input_get_mouse_x();
/*
* Gets the mouse y coordinate
*
* @returns The y coordinate of mouse
*/
float input_get_mouse_y();
/*
* Gets the amount the mouse moved horizontally since the last frame
*
* @returns The Δx coordinate of mouse
*/
float input_get_mouse_dx();
/*
* Gets the amount the mouse moved vertically since the last frame
*
* @returns The Δy coordinate of mouse
*/
float input_get_mouse_dy();
/*
* Gets the amount the mouse wheel has been scrolled vertically
*
* @returns The scroll amount
*/
float input_get_mouse_scroll();

bool input_is_key_down(uint32_t key);
char* input_get_keys_typed();
bool input_is_key_pressed(uint32_t key);
bool input_is_key_released(uint32_t key);

void input_key_listener(uint32_t key, bool pressed);
void input_type_listener(char key);
