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

	out_board->game_object = scene_new_object(scene);
	obj_loader_load_model("assets/models/board_placeholder.obj", &out_board->game_object->model.mesh);
	texture_create("assets/images/board.bmp", &out_board->game_object->model.model_texture);

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

			game_object_t* object = out_board->piece_objects[i * 4 + j] = scene_new_object(scene);
			obj_loader_load_model("assets/models/piece_placeholder.obj", &object->model.mesh);

			object->colour = colour;
			object->transform.position = vec3_add(base_position, vec3_create(x_axis * step_size, 0.0f, y_axis * step_size));
			object->transform.scale = vec3_scalar(game_scale);
			object->index = (i * 4) + j + 1;
		}
	}

	for (uint32_t i = 0; i < 40; i++)
	{
		game_object_t* object = out_board->field_objects[i] = scene_new_object(scene);
		obj_loader_load_model("assets/models/board_field_placeholder.obj", &object->model.mesh);

		object->transform.position = _board_get_field_position(i);
	}

	return true;
}

void board_destroy(board_t* board)
{
	memset(board, 0, sizeof(board_t));
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
