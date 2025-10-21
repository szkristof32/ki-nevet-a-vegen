#include "game_object.h"

#include "infoc/math/utilities.h"

mat4 transform_get_model_matrix(transform_t* transform)
{
	mat4 matrix = mat4_identity();
	matrix = mat4_scale_vec3(matrix, transform->scale);
	matrix = mat4_rotate_x(matrix, deg_to_rad(transform->rotation.x));
	matrix = mat4_rotate_y(matrix, deg_to_rad(transform->rotation.y));
	matrix = mat4_rotate_z(matrix, deg_to_rad(transform->rotation.z));
	matrix = mat4_translate(matrix, vec4_create(transform->position.x, transform->position.y, transform->position.z, 1.0f));

	return matrix;
}
