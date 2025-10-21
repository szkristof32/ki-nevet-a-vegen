#include "camera.h"

mat4 camera_get_view_matrix(camera_t* camera)
{
	mat4 model_matrix = transform_get_model_matrix(&camera->transform);

	return mat4_invert(model_matrix);
}
