#pragma once

#include "infoc/core/defines.h"

#include "menu_state.h"

/**
 * Attach callback for new game menu
 *
 * @returns The internal data of the menu
 */
void* new_game_menu_attach();
/**
 * Detach callback for new game menu
 *
 * @param menu_data The internal data of the menu
 */
void new_game_menu_detach(void* menu_data);
/**
 * Draws the new game menu
 *
 * @param window_width, window_height Window dimensions
 * @param menu_data The internal data of the menu
 */
menu_state draw_new_game_menu(uint32_t window_width, uint32_t window_height, void* menu_data);
