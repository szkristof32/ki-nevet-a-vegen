#include "board.h"

#include "infoc/math/vec3.h"

#include "infoc/utils/obj_loader.h"

#include <string.h>

bool board_create(scene_t* scene, board_t* out_board)
{
	memset(out_board, 0, sizeof(board_t));

	out_board->game_object = scene_new_object(scene);
	obj_loader_load_model("assets/models/board_placeholder.obj", &out_board->game_object->model.mesh);

	const float board_size = 15.0f;
	const float home_size = 1.75f;

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
			object->transform.position = vec3_add(base_position, vec3_create(x_axis * home_size, 0.0f, y_axis * home_size));
			object->transform.scale = vec3_scalar(0.125f);
			object->index = (i * 4) + j + 1;
		}
	}

	return true;
}

void board_destroy(board_t* board)
{
	memset(board, 0, sizeof(board_t));
}
