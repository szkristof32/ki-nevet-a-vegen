#pragma once

#include "defines.h"

bool input_initialise();
void input_shutdown();

void input_update();

void input_move_listener(float x, float y);
void input_click_listener(int button, bool pressed);
void input_scroll_listener(float scroll_x, float scroll_y);

bool input_is_mouse_button_down(uint32_t button);

float input_get_mouse_x();
float input_get_mouse_y();
float input_get_mouse_dx();
float input_get_mouse_dy();
float input_get_mouse_scroll();
