#include "board.h"

#include "infoc/math/vec3.h"

#include "infoc/utils/obj_loader.h"

#include <string.h>

bool board_create(scene_t* scene, board_t* out_board)
{
	memset(out_board, 0, sizeof(board_t));

	out_board->game_object = scene_new_object(scene);
	obj_loader_load_model("assets/models/board_placeholder.obj", &out_board->game_object->model.mesh);

	for (uint32_t i = 0; i < 4; i++)
	{
		vec4 colour = vec4_create(i % 3 == 0, i % 2 == 1, i == 2, 1.0f);
		for (uint32_t j = 0; j < 4; j++)
		{
			game_object_t* object = out_board->piece_objects[i * 4 + j] = scene_new_object(scene);
			obj_loader_load_model("assets/models/piece_placeholder.obj", &object->model.mesh);

			object->colour = colour;
			object->transform.position = vec3_create((i * 4 + j) * 2.5f, 0.0f, 0.0f);
			object->transform.scale = vec3_scalar(0.125f);
		}
	}

	return true;
}

void board_destroy(board_t* board)
{
	memset(board, 0, sizeof(board_t));
}
