#pragma once

#include "infoc/core/layers.h"

/*
* Creates the game layer
*
* @returns The game layer (type `layer_t`)
*/
layer_t game_layer_create();

void game_layer_set_game_name(char* game_name);
