#pragma once

#include "infoc/core/defines.h"

#include "infoc/scene/scene.h"

#include "infoc/math/vec2.h"

typedef struct piece_t
{
	uint32_t player_index;
	uint32_t position;
	uint32_t object_index;
} piece_t;

typedef struct board_t
{
	piece_t pieces[40];
	piece_t pieces_in_house[4][4];
	game_object_index_t game_object;
	game_object_index_t piece_objects[4 * 4];

	game_object_index_t field_objects[40];

	scene_t* scene;
} board_t;

bool board_create(scene_t* scene, board_t* out_board);
void board_destroy(board_t* board);

// Returns a darray
vec3* board_make_move(board_t* board, uint32_t object_index, uint32_t player_index, uint32_t move);
bool board_is_piece_in_house(board_t* board, uint32_t object_index);
