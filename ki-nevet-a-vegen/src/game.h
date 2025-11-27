#pragma once

#include "infoc/scene/game_object.h"

#include "dice.h"

/**
 * Enumeration for player types
 */
typedef enum player_type
{
	player_computer,
	player_human
} player_type;

/**
 * Configuration for the game
 */
typedef struct game_configuration_t
{
	/** Game name (should be freed after use) */
	char* game_name;
	/** Dice */
	dice_t dice;
	/** Players (human or computer) */
	player_type players[4];
} game_configuration_t;

/**
 * Enumeration for the players
 */
typedef enum player_enum
{
	player_red,
	player_blue,
	player_green,
	player_yellow
} player_enum;

/**
 * Information about a move
 */
typedef struct move_t
{
	/** The player */
	player_enum player;
	/** The number of steps */
	uint32_t move_count;
	/** The piece index */
	game_object_index_t object;
} move_t;

/** 
 * Game save
 */
typedef struct game_save_t
{
	/** Configuration */
	game_configuration_t configuration;
	/** Dynamic array of moves */
	move_t* moves;
} game_save_t;

/**
 * Loads a savegame from disk
 * 
 * @param path The filepath
 * @param out_save A pointer to a `game_save_t` struct to be filled with game information
 */
void game_load_save(const char* path, game_save_t* out_save);

#ifndef min
/**
* Returns the minimum of `a` and `b`
*
* @warning Can produce unexpected side-effects when `a` or `b` is directly manipulated when passed in (eg. `min(a++, b)`)
*/
#define min(a, b) ((a)<(b)?(a):(b))
#endif
#ifndef max
/**
* Returns the maximum of `a` and `b`
*
* @warning Can produce unexpected side-effects when `a` or `b` is directly manipulated when passed in (eg. `max(a++, b)`)
*/
#define max(a, b) ((a)>(b)?(a):(b))
#endif
