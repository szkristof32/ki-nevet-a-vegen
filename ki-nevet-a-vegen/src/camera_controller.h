#pragma once

#include "infoc/core/defines.h"

#include "infoc/scene/camera.h"

/*
* Camera controller for scene camera
*/
typedef struct camera_controller_t
{
	camera_t* camera; /* Non-owning reference to a camera */

	vec3 center; /* Center point to look at */
	float distance_from_center; /* Distance from center point */
	
	float angle_around_center; /* The angle rotated around the center point */
	float pitch; /* Camera pitch (rotation along the x axis) */

	bool is_moving;
} camera_controller_t;

/*
* Calculates the camera position and the view matrix
*
* @param controller A pointer to a valid `camera_controller_t` struct
*/
void camera_controller_update(camera_controller_t* controller, bool enable_moving);
