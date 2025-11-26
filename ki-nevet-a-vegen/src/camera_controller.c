#include "camera_controller.h"

#include "game.h"

#include "infoc/core/input.h"

#include "infoc/math/utilities.h"

#include <math.h>

static void _check_inputs(camera_controller_t* controller, bool enable_moving);

void camera_controller_update(camera_controller_t* controller, bool enable_moving)
{
	camera_t* camera = controller->camera;
	
	_check_inputs(controller, enable_moving);

	float pitch = deg_to_rad(controller->pitch);
	float horizontal_distance = controller->distance_from_center * cosf(pitch);
	float vertical_distance = controller->distance_from_center * sinf(pitch);
	float theta = deg_to_rad(controller->angle_around_center);

	camera->position.x = controller->center.x + (horizontal_distance * sinf(theta));
	camera->position.y = controller->center.y + vertical_distance;
	camera->position.z = controller->center.z + (horizontal_distance * cosf(theta));

	camera->view_matrix = mat4_look_at(camera->position, controller->center, vec3_create(0.0f, 1.0f, 0.0f));
}

void _check_inputs(camera_controller_t* controller, bool enable_moving)
{
	{
		float zoom_level = input_get_mouse_scroll();
		controller->distance_from_center -= zoom_level;
		controller->distance_from_center = max(controller->distance_from_center, 0.5f);
	}

	if (input_is_mouse_button_down(mouse_button_left) && enable_moving)
	{
		float dx = input_get_mouse_dx();
		float dy = input_get_mouse_dy();

		controller->angle_around_center -= dx * 150.0f;
		controller->pitch += dy * 150.0f;

		controller->pitch = max(min(controller->pitch, 89.95f), 0.05f);

		controller->is_moving = !(fabs(dx) < 0.02f || fabs(dy) < 0.02f);
	}
	else
	{
		controller->is_moving = false;
	}
}
