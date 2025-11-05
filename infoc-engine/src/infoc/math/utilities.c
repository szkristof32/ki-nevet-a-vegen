#include "utilities.h"

#include <math.h>

float deg_to_rad(float deg)
{
	return deg / 180.0f * PI;
}

float rad_to_deg(float rad)
{
	return rad / PI * 180.0f;
}

mat4 mat4_translate(mat4 matrix, vec4 vector)
{
	vec4 v1 = vec4_scale(matrix.rows[0], vector.x);
	vec4 v2 = vec4_scale(matrix.rows[1], vector.y);
	vec4 v3 = vec4_scale(matrix.rows[2], vector.z);

	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	matrix.rows[3] = vec4_add(matrix.rows[3], v2);
	matrix.rows[3] = vec4_add(matrix.rows[3], v3);

	return matrix;
}

mat4 mat4_translate_x(mat4 matrix, float x)
{
	vec4 v1 = vec4_scale(matrix.rows[0], x);
	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	return matrix;
}

mat4 mat4_translate_y(mat4 matrix, float y)
{
	vec4 v1 = vec4_scale(matrix.rows[1], y);
	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	return matrix;
}

mat4 mat4_translate_z(mat4 matrix, float z)
{
	vec4 v1 = vec4_scale(matrix.rows[2], z);
	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	return matrix;
}

mat4 mat4_rotate_x(mat4 matrix, float angle_rad)
{
	float c = cosf(angle_rad);
	float s = sinf(angle_rad);

	mat4 result = mat4_identity();
	result.values[1][1] = c;
	result.values[1][2] = s;
	result.values[2][1] = -s;
	result.values[2][2] = c;

	return mat4_mul_rot(matrix, result);
}

mat4 mat4_rotate_y(mat4 matrix, float angle_rad)
{
	float c = cosf(angle_rad);
	float s = sinf(angle_rad);

	mat4 result = mat4_identity();
	result.values[0][0] = c;
	result.values[0][2] = -s;
	result.values[2][0] = s;
	result.values[2][2] = c;

	return mat4_mul_rot(matrix, result);
}

mat4 mat4_rotate_z(mat4 matrix, float angle_rad)
{
	float c = cosf(angle_rad);
	float s = sinf(angle_rad);

	mat4 result = mat4_identity();
	result.values[0][0] = c;
	result.values[0][1] = s;
	result.values[1][0] = -s;
	result.values[1][1] = c;

	return mat4_mul_rot(matrix, result);
}

mat4 mat4_scale_vec3(mat4 matrix, vec3 scalar)
{
	matrix.values[0][0] *= scalar.x;
	matrix.values[1][1] *= scalar.y;
	matrix.values[2][2] *= scalar.z;

	return matrix;
}

mat4 mat4_scale_vec4(mat4 matrix, vec4 scalar)
{
	matrix.values[0][0] *= scalar.x;
	matrix.values[1][1] *= scalar.y;
	matrix.values[2][2] *= scalar.z;
	matrix.values[3][3] *= scalar.w;

	return matrix;
}

mat4 mat4_perspective(float fov, float aspect_ratio, float near_plane, float far_plane)
{
	float f = 1.0f / tanf(fov / 2.0f);
	float fn = 1.0f / (near_plane - far_plane);

	mat4 result = { 0 };
	result.values[0][0] = f / aspect_ratio;
	result.values[1][1] = f;
	result.values[2][2] = (near_plane + far_plane) * fn;
	result.values[2][3] = -1.0f;
	result.values[3][2] = 2.0f * near_plane * far_plane * fn;

	return result;
}

mat4 mat4_look_at(vec3 eye, vec3 center, vec3 up)
{
	vec3 f = vec3_normalise(vec3_sub(center, eye));
	vec3 s = vec3_normalise(vec3_cross(f, up));
	vec3 u = vec3_cross(s, f);

	mat4 result = mat4_identity();
	result.values[0][0] = s.x;
	result.values[0][1] = u.x;
	result.values[0][2] = -f.x;
	result.values[1][0] = s.y;
	result.values[1][1] = u.y;
	result.values[1][2] = -f.y;
	result.values[2][0] = s.z;
	result.values[2][1] = u.z;
	result.values[2][2] = -f.z;
	result.values[3][0] = -vec3_dot(s, eye);
	result.values[3][1] = -vec3_dot(u, eye);
	result.values[3][2] = vec3_dot(f, eye);
	result.values[0][3] = result.rows[1].w = result.rows[2].w = 0.0f;
	result.values[3][3] = 1.0f;

	return result;
}
