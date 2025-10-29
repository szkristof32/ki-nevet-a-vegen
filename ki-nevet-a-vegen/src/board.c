#include "board.h"

#include "infoc/math/vec3.h"

#include "infoc/utils/obj_loader.h"

#include <string.h>

static const float game_scale = 0.125f;
static const float board_size = 18.0f;
static const float step_size = 2.0f;

vec3 _board_get_field_position(uint32_t index);

bool board_create(scene_t* scene, board_t* out_board)
{
	memset(out_board, 0, sizeof(board_t));

	out_board->scene = scene;
	out_board->game_object = scene_new_object(scene);
	game_object_t* board_object = scene_get_object(scene, out_board->game_object);
	obj_loader_load_model("assets/models/board_placeholder.obj", &board_object->model.mesh);
	texture_create("assets/images/board.bmp", &board_object->model.model_texture);

	for (uint32_t i = 0; i < 4; i++)
	{
		float x_axis = (float)(-(i % 3 == 0) + (i % 3 != 0));
		float y_axis = (float)(-(i % 2 == 0) + (i % 2 != 0));

		vec3 base_position = vec3_create(x_axis * board_size, 0.0f, y_axis * board_size);
		vec4 colour = vec4_create((float)(i % 3 == 0), (float)(i % 2 == 1), (float)(i == 2), 1.0f);

		for (uint32_t j = 0; j < 4; j++)
		{
			float x_axis = (float)(-(j % 3 == 0) + (j % 3 != 0));
			float y_axis = (float)(-(j % 2 == 0) + (j % 2 != 0));

			game_object_index_t object_index = out_board->piece_objects[i * 4 + j] = scene_new_object(scene);
			game_object_t* object = scene_get_object(scene, object_index);
			obj_loader_load_model("assets/models/piece_placeholder.obj", &object->model.mesh);

			object->colour = colour;
			object->transform.position = vec3_add(base_position, vec3_create(x_axis * step_size, 0.0f, y_axis * step_size));
			object->transform.scale = vec3_scalar(game_scale);
			object->index = (i * 4) + j + 1;
		}
	}

	for (uint32_t i = 0; i < 40; i++)
	{
		game_object_index_t object_index = out_board->field_objects[i] = scene_new_object(scene);
		game_object_t* object = scene_get_object(scene, object_index);
		obj_loader_load_model("assets/models/board_field_placeholder.obj", &object->model.mesh);

		object->transform.position = _board_get_field_position(i);
	}

	return true;
}

void board_destroy(board_t* board)
{
	memset(board, 0, sizeof(board_t));
}

void board_make_move(board_t* board, uint32_t object_index, uint32_t player_index, uint32_t move)
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
	{
		memmove(&board->pieces[position + move], &board->pieces[position], sizeof(piece_t));
		position += move;
	}
	else
	{
		uint32_t player_start = player_index * 10;
		position = player_start + move;

		piece_t* piece = &board->pieces[position];
		piece->object_index = object_index;
		piece->player_index = player_index;
	}

	board->pieces[position].position = position;
	scene_get_object(board->scene, board->piece_objects[object_index])->transform.position = _board_get_field_position(position);
}

vec3 _board_get_field_position(uint32_t index)
{
	const struct
	{
		uint32_t step_count;
		vec2 step_direction;
	} steps[12] = {
		{ 4, vec2_create( 1.0f,  0.0f) },
		{ 4, vec2_create( 0.0f, -1.0f) },
		{ 2, vec2_create( 1.0f,  0.0f) },
		{ 4, vec2_create( 0.0f,  1.0f) },
		{ 4, vec2_create( 1.0f,  0.0f) },
		{ 2, vec2_create( 0.0f,  1.0f) },
		{ 4, vec2_create(-1.0f,  0.0f) },
		{ 4, vec2_create( 0.0f,  1.0f) },
		{ 2, vec2_create(-1.0f,  0.0f) },
		{ 4, vec2_create( 0.0f, -1.0f) },
		{ 4, vec2_create(-1.0f,  0.0f) },
		{ 2, vec2_create( 0.0f, -1.0f) },
	};

	float pos_x = (-board_size - step_size) * game_scale;
	float pos_z = -step_size * 2.0f * game_scale;

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
