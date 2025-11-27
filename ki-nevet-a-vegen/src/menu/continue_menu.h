#pragma once

#include "infoc/core/defines.h"

#include "menu_state.h"

/**
 * Attach callback for continue menu
 * 
 * @returns The internal data of the menu
 */
void* continue_menu_attach();
/**
 * Detach callback for continue menu
 * 
 * @param menu_data The internal data of the menu
 */
void continue_menu_detach(void* menu_data);
/**
 * Draws the continue menu
 * 
 * @param window_width, window_height Window dimensions
 * @param menu_data The internal data of the menu
 */
menu_state draw_continue_menu(uint32_t window_width, uint32_t window_height, void* menu_data);
