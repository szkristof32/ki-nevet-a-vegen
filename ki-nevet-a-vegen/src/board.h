#pragma once

#include "infoc/core/defines.h"

#include "infoc/scene/scene.h"

#include "infoc/math/vec2.h"

typedef struct piece_t
{
	uint8_t player_id;
	vec2 position;
} piece_t;

typedef struct board_t
{
	piece_t pieces[40];
	game_object_t* game_object;
	game_object_t* piece_objects[4 * 4];

	game_object_t* field_objects[40];
} board_t;

bool board_create(scene_t* scene, board_t* out_board);
void board_destroy(board_t* board);
