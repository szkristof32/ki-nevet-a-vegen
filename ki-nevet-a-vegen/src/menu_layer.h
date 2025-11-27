#pragma once

#include "infoc/core/layers.h"

/**
 * Creates the menu layer
 *
 * @returns The menu layer (type `layer_t`)
 */
layer_t menu_layer_create(layer_t* game_layer);
/**
 * Transitions to the menu
 */
void menu_layer_transition_to();
