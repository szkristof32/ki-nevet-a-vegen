#pragma once

#include "infoc/core/layers.h"

#include "game.h"

/**
 * Creates the game layer
 *
 * @returns The game layer (type `layer_t`)
 */
layer_t game_layer_create();

/**
 * Loads a game from a savegame
 * 
 * @param save The loaded information about a game
 */
void game_load(const game_save_t* save);
/**
 * Configures a game
 * 
 * @param configuration The configuration
 */
void game_configure(const game_configuration_t* configuration);
