#pragma once

#include "dice.h"

typedef enum player_type
{
	player_computer,
	player_human
} player_type;

typedef struct game_configuration_t
{
	const char* game_name;
	dice_t dice;
	player_type players[4];
} game_configuration_t;

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