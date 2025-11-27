#pragma once

#include "game_object.h"

/**
 * Camera
 */
typedef struct camera_t
{
	/** Camera position */
	vec3 position;
	/** Camera view matrix */
	mat4 view_matrix;
} camera_t;
