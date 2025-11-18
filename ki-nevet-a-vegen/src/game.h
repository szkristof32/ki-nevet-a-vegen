#pragma once

#include "infoc/scene/game_object.h"

#include "dice.h"

typedef enum player_type
{
	player_computer,
	player_human
} player_type;

typedef struct game_configuration_t
{
	char* game_name;
	dice_t dice;
	player_type players[4];
} game_configuration_t;

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

typedef struct move_t
{
	player_enum player;
	uint32_t move_count;
	game_object_index_t object;
} move_t;

typedef struct game_save_t
{
	game_configuration_t configuration;
	move_t* moves; // darray
} game_save_t;

#ifndef min
/*
* Returns the minimum of `a` and `b`
*
* @warning Can produce unexpected side-effects when `a` or `b` is directly manipulated when passed in (eg. `min(a++, b)`)
*/
#define min(a, b) ((a)<(b)?(a):(b))
#endif
#ifndef max
/*
* Returns the maximum of `a` and `b`
*
* @warning Can produce unexpected side-effects when `a` or `b` is directly manipulated when passed in (eg. `max(a++, b)`)
*/
#define max(a, b) ((a)>(b)?(a):(b))
#endif