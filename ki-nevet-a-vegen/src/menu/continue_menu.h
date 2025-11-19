#pragma once

#include "infoc/core/defines.h"

#include "menu_state.h"

void* continue_menu_attach();
void continue_menu_detach(void* menu_data);
menu_state draw_continue_menu(uint32_t window_width, uint32_t window_height, void* menu_data);
