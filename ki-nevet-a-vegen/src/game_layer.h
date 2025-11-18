#pragma once

#include "infoc/core/layers.h"

#include "game.h"

/*
* Creates the game layer
*
* @returns The game layer (type `layer_t`)
*/
layer_t game_layer_create();

void game_configure(const game_configuration_t* configuration);
