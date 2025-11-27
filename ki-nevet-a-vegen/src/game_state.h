#pragma once

#include "game.h"
#include "board.h"
#include "dice.h"

/**
 * Core game state
 */
typedef struct game_state_t
{
	/** The currently playing player */
	player_enum player_to_go;
	/** The last number rolled by any player */
	uint32_t rolled;

	/** The game board */
	board_t board;
	/** The index of the object currently hovered */
	uint32_t hovered_object;
	/** Delta time */
	float delta;
	/** The winner player */
	player_enum winner;

	/** Configuration */
	const game_configuration_t* configuration;
	/** Internal game state data, not exposed */
	void* internal_state;
} game_state_t;

/**
 * Creates a game state
 *
 * @param scene A reference to the scene
 * @param out_game_state A pointer to a `game_state_t` struct to be filled
 * @param configuration A pointer to a valid `game_configuration_t` struct
 *
 * @warning Game state does not own the scene therefore it should be freed elsewhere
 */
void game_state_create(scene_t* scene, game_state_t* out_game_state, const game_configuration_t* configuration);
/**
 * Destroys the game state
 *
 * @param game_state A pointer to a valid `game_state_t` struct
 *
 * @warning Since game state doesn't own the scene it should be freed after use elsewhere
 */
void game_state_destroy(game_state_t* game_state);

/**
 * Updates the game state and logic
 *
 * @param game_state A pointer to a valid `game_state_t` struct
 * @param hovered_object The index of the object the mouse is currently hovering over
 * @param delta The game delta in seconds
 * @param enable_ui_input A boolean indicating if the ui input is enabled
 */
void game_state_update(game_state_t* game_state, uint32_t hovered_object, float delta, bool enable_ui_input);
/**
 * Renders the game state UI using SDL
 *
 * @param game_state A pointer to a valid `game_state_t` struct
 * @param renderer The SDL renderer
 */
bool game_state_render_ui(game_state_t* game_state);

/**
 * Plays a move
 *
 * @param game_state A pointer to a valid `game_state_t` struct
 * @param move A pointer to a valid `move_t` struct
 * @param animate A boolean indicating if the move should be animated or played instantly
 */
void game_state_play_move(game_state_t* game_state, const move_t* move, bool animate);
/**
 * Saves the current game state
 * 
 * @param game_state A pointer to a valid `game_state_t` struct
 */
void game_state_save(game_state_t* game_state);
