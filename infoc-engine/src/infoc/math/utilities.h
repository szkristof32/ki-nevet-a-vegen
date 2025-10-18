#pragma once

#include "mat4.h"

#include <math.h>

#define PI (3.141592654f)

inline float deg_to_rad(float deg)
{
	return deg / 180.0f * PI;
}

inline float rad_to_deg(float rad)
{
	return rad / PI * 180.0f;
}

inline mat4 mat4_perspective(float fov, float aspect_ratio, float near_plane, float far_plane)
{
	float f = 1.0f / tanf(fov / 2.0f);
	float fn = 1.0f / (near_plane - far_plane);

	mat4 result = { 0 };
	result.rows[0].x = f / aspect_ratio;
	result.rows[1].y = f;
	result.rows[2].z = (near_plane + far_plane) * fn;
	result.rows[2].w = -1.0f;
	result.rows[3].z = 2.0f * near_plane * far_plane * fn;

	return result;
}

inline mat4 mat4_translate(mat4 matrix, vec4 vector)
{
	vec4 v1 = vec4_mul(matrix.rows[2], vector);
	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	return matrix;
}

inline mat4 mat4_translate_x(mat4 matrix, float x)
{
	vec4 v1 = vec4_scale(matrix.rows[2], x);
	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	return matrix;
}

inline mat4 mat4_translate_y(mat4 matrix, float y)
{
	vec4 v1 = vec4_scale(matrix.rows[2], y);
	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	return matrix;
}

inline mat4 mat4_translate_z(mat4 matrix, float z)
{
	vec4 v1 = vec4_scale(matrix.rows[2], z);
	matrix.rows[3] = vec4_add(matrix.rows[3], v1);
	return matrix;
}

inline mat4 mat4_rotate_x(mat4 matrix, float angle_rad)
{
	float c = cosf(angle_rad);
	float s = sinf(angle_rad);

	mat4 result = mat4_identity();
	result.rows[1].y = c;
	result.rows[1].z = s;
	result.rows[2].y = -s;
	result.rows[2].z = c;

	return mat4_mul_rot(matrix, result);
}

inline mat4 mat4_rotate_y(mat4 matrix, float angle_rad)
{
	float c = cosf(angle_rad);
	float s = sinf(angle_rad);

	mat4 result = mat4_identity();
	result.rows[0].x = c;
	result.rows[0].z = -s;
	result.rows[2].x = s;
	result.rows[2].z = c;

	return mat4_mul_rot(matrix, result);
}

inline mat4 mat4_rotate_z(mat4 matrix, float angle_rad)
{
	float c = cosf(angle_rad);
	float s = sinf(angle_rad);

	mat4 result = mat4_identity();
	result.rows[0].x = c;
	result.rows[0].y = s;
	result.rows[1].x = -s;
	result.rows[1].y = c;

	return mat4_mul_rot(matrix, result);
}
