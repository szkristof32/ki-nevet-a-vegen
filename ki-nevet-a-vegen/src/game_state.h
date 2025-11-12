#pragma once

#include "board.h"
#include "dice.h"

#include <SDL3/SDL_render.h>

/*
* Enumeration for the players
*/
typedef enum player_enum
{
	player_red,
	player_blue,
	player_green,
	player_yellow
} player_enum;

/*
* Core game state
*/
typedef struct game_state_t
{
	dice_t dice; /* Dice */
	player_enum player_to_go; /* The currently playing player */
	uint32_t rolled; /* The last number rolled by any player */

	board_t board;
	uint32_t hovered_object;
	float delta;
	player_enum winner;

	void* internal_state; /* Internal game state data, not exposed */
} game_state_t;

/*
* Creates a game state
*
* @param scene A reference to the scene
* @param out_game_state A pointer to a `game_state_t` struct to be filled
*
* @warning Game state does not own the scene therefore it should be freed elsewhere
*/
void game_state_create(scene_t* scene, game_state_t* out_game_state);
/*
* Destroys the game state
*
* @param game_state A pointer to a valid `game_state_t` struct
*
* @warning Since game state doesn't own the scene it should be freed after use elsewhere
*/
void game_state_destroy(game_state_t* game_state);

/*
* Updates the game state and logic
*
* @param game_state A pointer to a valid `game_state_t` struct
* @param hovered_object The index of the object the mouse is currently hovering over
* @param delta The game delta in seconds
*/
void game_state_update(game_state_t* game_state, uint32_t hovered_object, float delta);
/*
* Renders the game state UI using SDL
*
* @param game_state A pointer to a valid `game_state_t` struct
* @param renderer The SDL renderer
*/
void game_state_render_ui(game_state_t* game_state, SDL_Renderer* renderer);
