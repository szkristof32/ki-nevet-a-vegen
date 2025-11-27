#pragma once

#include "infoc/core/defines.h"

#include "infoc/scene/camera.h"

/**
* Camera controller for scene camera
*/
typedef struct camera_controller_t
{
	/** Non-owning reference to a camera */
	camera_t* camera;

	/** Center point to look at */
	vec3 center;
	/** Distance from center point */
	float distance_from_center;
	
	/** The angle rotated around the center point */
	float angle_around_center;
	/** Camera pitch (rotation along the x axis) */
	float pitch;

	/** Singal if the camera is moving this frame */
	bool is_moving;
} camera_controller_t;

/**
 * Calculates the camera position and the view matrix
 *
 * @param controller A pointer to a valid `camera_controller_t` struct
 * @param enable_moving A boolean indicating if the camera is allowed to move
 */
void camera_controller_update(camera_controller_t* controller, bool enable_moving);
