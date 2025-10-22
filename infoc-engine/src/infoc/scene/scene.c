#include "scene.h"

#include "infoc/core/darray.h"

#include <string.h>

void scene_create(scene_t* out_scene)
{
	memset(out_scene, 0, sizeof(scene_t));

	out_scene->game_objects = darray_create(game_object_t);
	out_scene->camera.view_matrix = mat4_identity();
}

void scene_destroy(scene_t* scene)
{
	for (uint32_t i = 0; i < darray_count(scene->game_objects); i++)
	{
		game_object_destroy(&scene->game_objects[i]);
	}

	darray_destroy(scene->game_objects);
	memset(scene, 0, sizeof(game_object_t));
}

game_object_t* scene_new_object(scene_t* scene)
{
	game_object_t object = { 0 };
	object.transform.scale = vec3_scalar(1.0f);
	object.colour = vec4_scalar(1.0f);

	darray_push(scene->game_objects, object);

	return &scene->game_objects[darray_count(scene->game_objects) - 1];
}
