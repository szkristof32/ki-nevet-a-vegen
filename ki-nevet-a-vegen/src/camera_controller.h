#pragma once

#include "infoc/core/defines.h"

#include "infoc/scene/camera.h"

typedef struct camera_controller_t
{
	camera_t* camera;

	vec3 center;
	float distance_from_center;
	
	float angle_around_center;
	float pitch;
} camera_controller_t;

void camera_controller_update(camera_controller_t* controller);
