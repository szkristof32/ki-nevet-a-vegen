#pragma once

#include "game_object.h"

typedef struct camera_t
{
	vec3 position;
	mat4 view_matrix;
} camera_t;
