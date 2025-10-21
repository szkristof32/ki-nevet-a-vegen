#pragma once

#include "game_object.h"
#include "camera.h"

typedef struct scene_t
{
	camera_t camera;
	game_object_t* game_objects; // darray
} scene_t;

void scene_create(scene_t* out_scene);
void scene_destroy(scene_t* scene);

game_object_t* scene_new_object(scene_t* scene);
