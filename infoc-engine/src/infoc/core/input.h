#pragma once

#include "defines.h"

typedef enum mouse_button
{
	mouse_button_left,
	mouse_button_right,
	mouse_button_middle
} mouse_button;

bool input_initialise();
void input_shutdown();

void input_update();

void input_move_listener(float x, float y);
void input_click_listener(int button, bool pressed);
void input_scroll_listener(float scroll_x, float scroll_y);

bool input_is_mouse_button_down(uint32_t button);
bool input_is_mouse_button_clicked(uint32_t button);
bool input_is_mouse_button_released(uint32_t button);

float input_get_mouse_x();
float input_get_mouse_y();
float input_get_mouse_dx();
float input_get_mouse_dy();
float input_get_mouse_scroll();
