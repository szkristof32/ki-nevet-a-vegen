#include "board.h"

#include "infoc/core/darray.h"

#include "infoc/math/vec3.h"

#include "infoc/utils/obj_loader.h"

#include <string.h>

static const float game_scale = 0.125f;
static const float board_size = 18.0f;
static const float step_size = 2.0f;

static vec3 _board_get_field_position(uint32_t index);
static vec3 _board_get_house_position(uint32_t player_index, uint32_t house_index);

bool board_create(scene_t* scene, board_t* out_board)
{
	memset(out_board, 0, sizeof(board_t));

	out_board->scene = scene;
	out_board->game_object = scene_new_object(scene);
	game_object_t* board_object = scene_get_object(scene, out_board->game_object);
	obj_loader_load_model("assets/models/board.model", &board_object->model.mesh);
	texture_create("assets/images/scene.png", &board_object->model.model_texture);

	for (uint32_t i = 0; i < 4; i++)
	{
		float x_axis = (float)(-(i % 3 == 0) + (i % 3 != 0));
		float y_axis = (float)(-(i % 4 <= 1) + (i % 4 >= 2));

		vec3 base_position = vec3_create(x_axis * board_size, 0.0f, y_axis * board_size);
		vec4 colour = vec4_create((float)(i % 3 == 0), (float)(i % 4 > 1), (float)(i == 1), 1.0f);

		for (uint32_t j = 0; j < 4; j++)
		{
			float x_axis = (float)(-(j % 3 == 0) + (j % 3 != 0));
			float y_axis = (float)(-(j % 2 == 0) + (j % 2 != 0));

			game_object_index_t object_index = out_board->piece_objects[i * 4 + j] = scene_new_object(scene);
			game_object_t* object = scene_get_object(scene, object_index);
			obj_loader_load_model("assets/models/piece.model", &object->model.mesh);

			object->colour = colour;
			object->transform.position = vec3_add(base_position, vec3_create(x_axis * step_size, 0.0f, y_axis * step_size));
			object->transform.scale = vec3_scalar(game_scale);
			object->index = (i * 4) + j + 1;
		}
	}

	return true;
}

void board_destroy(board_t* board)
{
	memset(board, 0, sizeof(board_t));
}

static bool _board_step(board_t* board, uint32_t object_index, uint32_t player_index, uint32_t destination);
static bool _is_position_in_house(uint32_t destination, uint32_t player_index);

board_move_t board_make_move(board_t* board, uint32_t object_index, uint32_t player_index, uint32_t move)
{
	uint32_t position = -1;
	for (uint32_t i = 0; i < 40; i++)
	{
		if (board->pieces[i].object_index == object_index)
		{
			position = board->pieces[i].position;
			break;
		}
	}

	uint32_t start_position = position;
	uint32_t player_start = player_index * 10;
	bool in_house = false;

	if (position == -1)
	{
		position = player_start - 1;
	}

	game_object_t* object = scene_get_object(board->scene, board->piece_objects[object_index - 1]);
	board_move_t board_move = { 0 };
	board_move.positions = darray_create(vec3);
	board_move.captured_pieces = darray_create(captured_piece_t);
	darray_push(board_move.positions, object->transform.position);

	int32_t step_direction = 1;

	while (move != 0)
	{
		bool in_house_next_step = _is_position_in_house(position + step_direction, player_index);
		uint32_t house_position = in_house ? position % 40 - player_start : -1;

		int32_t step_size = step_direction;
		while (!_board_step(board, object_index, player_index, position + step_size) ||
			(in_house_next_step && house_position + step_size >= 4) || step_size == 0)
		{
			if (in_house && house_position + step_size >= 4)
				step_direction = -1;
			step_size += step_direction;

			in_house_next_step = _is_position_in_house(position + step_size, player_index);
		}
		position += step_size;
		house_position = in_house_next_step ? position % 40 - player_start : -1;

		if (!in_house_next_step && board->pieces[position % 40].object_index != 0)
		{
			captured_piece_t capture = {
				.object_index = board->pieces[position % 40].object_index,
				.step = (uint32_t)darray_count(board_move.positions)
			};
			darray_push(board_move.captured_pieces, capture);
			memset(&board->pieces[position % 40], 0, sizeof(piece_t));
		}

		if (in_house_next_step)
		{
			darray_push(board_move.positions, vec3_mul(_board_get_house_position(player_index, house_position), vec3_inv(object->transform.scale)));
			in_house = true;
		}
		else
		{
			darray_push(board_move.positions, vec3_mul(_board_get_field_position(position), vec3_inv(object->transform.scale)));
			in_house = false;
		}

		move--;
	}

	uint32_t house_position = in_house ? position % 40 - player_start : -1;

	if (start_position != -1)
	{
		if (!_is_position_in_house(start_position, player_index))
			memset(&board->pieces[start_position % 40], 0, sizeof(piece_t));
		else
			memset(&board->pieces_in_house[player_index][house_position], 0, sizeof(piece_t));
	}

	piece_t* piece = NULL;
	if (!in_house)
	{
		piece = &board->pieces[position % 40];
	}
	else
	{
		piece = &board->pieces_in_house[player_index][house_position];
	}
	piece->player_index = player_index;
	piece->object_index = object_index;
	piece->position = position;

	return board_move;
}

bool _is_position_in_house(uint32_t destination, uint32_t player_index)
{
	uint32_t player_start = player_index * 10;

	return destination >= player_start + 40;
}

bool board_is_piece_in_house(board_t* board, uint32_t object_index)
{
	uint32_t position = -1;
	for (uint32_t i = 0; i < 40; i++)
	{
		if (board->pieces[i].object_index == object_index)
		{
			position = i;
			break;
		}
	}

	if (position != -1)
		return false;

	position = -1;
	for (uint32_t i = 0; i < 4; i++)
	{
		for (uint32_t j = 0; j < 4; j++)
		{
			if (board->pieces_in_house[i][j].object_index == object_index)
			{
				position = i;
				return true;
			}
		}
	}

	return false;
}

vec3 board_get_piece_start_position(board_t* board, game_object_index_t object_index)
{
	uint32_t player_index = (object_index - 1) / 4;
	uint32_t piece_index = (object_index - 1) % 4;

	float x_axis = (float)(-(player_index % 3 == 0) + (player_index % 3 != 0));
	float y_axis = (float)(-(player_index % 4 <= 1) + (player_index % 4 >= 2));

	vec3 base_position = vec3_create(x_axis * board_size, 0.0f, y_axis * board_size);

	x_axis = (float)(-(piece_index % 3 == 0) + (piece_index % 3 != 0));
	y_axis = (float)(-(piece_index % 2 == 0) + (piece_index % 2 != 0));

	return vec3_add(base_position, vec3_create(x_axis * step_size, 0.0f, y_axis * step_size));
}

bool _board_step(board_t* board, uint32_t object_index, uint32_t player_index, uint32_t destination)
{
	uint32_t player_start = player_index * 10;

	if (!_is_position_in_house(destination, player_index))
	{
		uint32_t piece_player_index = board->pieces[destination % 40].player_index;
		uint32_t piece_object_index = board->pieces[destination % 40].object_index;
		return piece_player_index != player_index || piece_object_index == 0;
	}

	uint32_t piece_player_index = board->pieces_in_house[player_index][(destination % 40 - player_start) % 4].player_index;
	uint32_t piece_object_index = board->pieces_in_house[player_index][(destination % 40 - player_start) % 4].object_index;
	return piece_player_index != player_index || piece_object_index == 0;
}

vec3 _board_get_field_position(uint32_t index)
{
	const struct
	{
		uint32_t step_count;
		vec2 step_direction;
	} steps[12] = {
		{ 4, vec2_create(1.0f,  0.0f) },
		{ 4, vec2_create(0.0f, -1.0f) },
		{ 2, vec2_create(1.0f,  0.0f) },
		{ 4, vec2_create(0.0f,  1.0f) },
		{ 4, vec2_create(1.0f,  0.0f) },
		{ 2, vec2_create(0.0f,  1.0f) },
		{ 4, vec2_create(-1.0f,  0.0f) },
		{ 4, vec2_create(0.0f,  1.0f) },
		{ 2, vec2_create(-1.0f,  0.0f) },
		{ 4, vec2_create(0.0f, -1.0f) },
		{ 4, vec2_create(-1.0f,  0.0f) },
		{ 2, vec2_create(0.0f, -1.0f) },
	};

	float pos_x = (-board_size - step_size) * game_scale;
	float pos_z = -step_size * 2.0f * game_scale;
	index %= 40;

	for (uint32_t i = 0; i < 12; i++)
	{
		if (index == 0)
			break;

		for (uint32_t j = 0; j < steps[i].step_count; j++)
		{
			if (index == 0)
				break;

			pos_x += 2.0f * step_size * game_scale * steps[i].step_direction.x;
			pos_z += 2.0f * step_size * game_scale * steps[i].step_direction.y;

			index--;
		}
	}

	return vec3_create(pos_x, 0.0f, pos_z);
}

vec3 _board_get_house_position(uint32_t player_index, uint32_t house_index)
{
	float pos_x = (board_size - (2.0f * house_index + 1) * step_size) * game_scale * (-(player_index == 0) + (player_index == 2));
	float pos_z = (board_size - (2.0f * house_index + 1) * step_size) * game_scale * (-(player_index == 1) + (player_index == 3));

	return vec3_create(pos_x, 0.0f, pos_z);
}
