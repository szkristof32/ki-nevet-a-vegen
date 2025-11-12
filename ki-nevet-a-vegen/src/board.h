#pragma once

#include "infoc/core/defines.h"

#include "infoc/scene/scene.h"

#include "infoc/math/vec2.h"

/*
* Game piece
*/
typedef struct piece_t
{
	uint32_t player_index; /* Owner player index (0=red, 1=blue, 2=green, 3=yellow) */
	uint32_t position; /* Position on the board (0-39, 0=red starting position) */
	uint32_t object_index; /* Corresponding game object index */
} piece_t;

typedef struct board_t
{
	piece_t pieces[40];
	piece_t pieces_in_house[4][4];
	game_object_index_t game_object;
	game_object_index_t piece_objects[4 * 4];

	game_object_index_t field_objects[40]; /* Stepping stone objects in the scene */

	scene_t* scene; /* Reference to the scene */
} board_t;

/*
* Creates a game board
*
* @param scene A pointer to the scene
* @param out_board A pointer to a `board_t` struct to be filled
*
* @returns A boolean indicating whether the operation was successful
*
* @warning The board does not own the scene, it should be freed elsewhere
*/
bool board_create(scene_t* scene, board_t* out_board);
/*
* Destroys a game board
*
* @param board A pointer to a valid `board_t` struct
*
* @warning Since the board doesn't own the scene, it should be freed elsewhere
*/
void board_destroy(board_t* board);

// Returns a darray
/*
* Generates the moves of the given piece
*
* @param board A pointer to a valid `board_t` struct
* @param object_index The resulting index of the piece from the mouse picking
* @param player_index The index of the current player (0=red, 1=blue, 2=green, 3=yellow)
* @param move The number of squares the piece should move when uninterrupted
*
* @returns A dynamic array of the generated move positions
*
* @warning The returned dynamic array should be freed after use using `darray_destroy`
*/
vec3* board_make_move(board_t* board, uint32_t object_index, uint32_t player_index, uint32_t move);
bool board_is_piece_in_house(board_t* board, uint32_t object_index);
