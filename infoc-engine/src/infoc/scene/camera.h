#pragma once

#include "game_object.h"

/*
* Camera
*/
typedef struct camera_t
{
	vec3 position; /* Camera position */
	mat4 view_matrix; /* Camera view matrix */
} camera_t;
