#pragma once

#include "board.h"
#include "dice.h"

#include <SDL3/SDL_render.h>

typedef enum player_enum
{
	player_red,
	player_blue,
	player_green,
	player_yellow
} player_enum;

typedef struct game_state_t
{
	dice_t dice;
	player_enum player_to_go;
	uint32_t rolled;

	board_t board;
	uint32_t hovered_object;

	void* internal_state;
} game_state_t;

void game_state_create(scene_t* scene, game_state_t* out_game_state);
void game_state_destroy(game_state_t* game_state);

void game_state_update(game_state_t* game_state, uint32_t hovered_object);
void game_state_render_ui(game_state_t* game_state, SDL_Renderer* renderer);
