#pragma once

#include "vec4.h"

typedef struct mat4
{
	vec4 rows[4];
} mat4;

mat4 mat4_identity()
{
	mat4 result = { 0 };
	result.rows[0].x = 1.0f;
	result.rows[1].y = 1.0f;
	result.rows[2].z = 1.0f;
	result.rows[3].w = 1.0f;
	return result;
}

mat4 mat4_mul(mat4 a, mat4 b)
{
	mat4 result = { 0 };
	result.rows[0].x = a.rows[0].x * b.rows[0].x + a.rows[1].x * b.rows[0].y + a.rows[2].x * b.rows[0].z + a.rows[3].x * b.rows[0].w;
	result.rows[0].y = a.rows[0].y * b.rows[0].x + a.rows[1].y * b.rows[0].y + a.rows[2].y * b.rows[0].z + a.rows[3].y * b.rows[0].w;
	result.rows[0].z = a.rows[0].z * b.rows[0].x + a.rows[1].z * b.rows[0].y + a.rows[2].z * b.rows[0].z + a.rows[3].z * b.rows[0].w;
	result.rows[0].w = a.rows[0].w * b.rows[0].x + a.rows[1].w * b.rows[0].y + a.rows[2].w * b.rows[0].z + a.rows[3].w * b.rows[0].w;
	result.rows[1].x = a.rows[0].x * b.rows[1].x + a.rows[1].x * b.rows[1].y + a.rows[2].x * b.rows[1].z + a.rows[3].x * b.rows[1].w;
	result.rows[1].y = a.rows[0].y * b.rows[1].x + a.rows[1].y * b.rows[1].y + a.rows[2].y * b.rows[1].z + a.rows[3].y * b.rows[1].w;
	result.rows[1].z = a.rows[0].z * b.rows[1].x + a.rows[1].z * b.rows[1].y + a.rows[2].z * b.rows[1].z + a.rows[3].z * b.rows[1].w;
	result.rows[1].w = a.rows[0].w * b.rows[1].x + a.rows[1].w * b.rows[1].y + a.rows[2].w * b.rows[1].z + a.rows[3].w * b.rows[1].w;
	result.rows[2].x = a.rows[0].x * b.rows[2].x + a.rows[1].x * b.rows[2].y + a.rows[2].x * b.rows[2].z + a.rows[3].x * b.rows[2].w;
	result.rows[2].y = a.rows[0].y * b.rows[2].x + a.rows[1].y * b.rows[2].y + a.rows[2].y * b.rows[2].z + a.rows[3].y * b.rows[2].w;
	result.rows[2].z = a.rows[0].z * b.rows[2].x + a.rows[1].z * b.rows[2].y + a.rows[2].z * b.rows[2].z + a.rows[3].z * b.rows[2].w;
	result.rows[2].w = a.rows[0].w * b.rows[2].x + a.rows[1].w * b.rows[2].y + a.rows[2].w * b.rows[2].z + a.rows[3].w * b.rows[2].w;
	result.rows[3].x = a.rows[0].x * b.rows[3].x + a.rows[1].x * b.rows[3].y + a.rows[2].x * b.rows[3].z + a.rows[3].x * b.rows[3].w;
	result.rows[3].y = a.rows[0].y * b.rows[3].x + a.rows[1].y * b.rows[3].y + a.rows[2].y * b.rows[3].z + a.rows[3].y * b.rows[3].w;
	result.rows[3].z = a.rows[0].z * b.rows[3].x + a.rows[1].z * b.rows[3].y + a.rows[2].z * b.rows[3].z + a.rows[3].z * b.rows[3].w;
	result.rows[3].w = a.rows[0].w * b.rows[3].x + a.rows[1].w * b.rows[3].y + a.rows[2].w * b.rows[3].z + a.rows[3].w * b.rows[3].w;

	return result;
}

mat4 mat4_mul_rot(mat4 a, mat4 b)
{
	mat4 result = { 0 };
	result.rows[0].x = a.rows[0].x * b.rows[0].x + a.rows[1].x * b.rows[0].y + a.rows[2].x * b.rows[0].z + a.rows[3].x * b.rows[0].w;
	result.rows[0].y = a.rows[0].y * b.rows[0].x + a.rows[1].y * b.rows[0].y + a.rows[2].y * b.rows[0].z + a.rows[3].y * b.rows[0].w;
	result.rows[0].z = a.rows[0].z * b.rows[0].x + a.rows[1].z * b.rows[0].y + a.rows[2].z * b.rows[0].z + a.rows[3].z * b.rows[0].w;
	result.rows[0].w = a.rows[0].w * b.rows[0].x + a.rows[1].w * b.rows[0].y + a.rows[2].w * b.rows[0].z + a.rows[3].w * b.rows[0].w;
	result.rows[1].x = a.rows[0].x * b.rows[1].x + a.rows[1].x * b.rows[1].y + a.rows[2].x * b.rows[1].z + a.rows[3].x * b.rows[1].w;
	result.rows[1].y = a.rows[0].y * b.rows[1].x + a.rows[1].y * b.rows[1].y + a.rows[2].y * b.rows[1].z + a.rows[3].y * b.rows[1].w;
	result.rows[1].z = a.rows[0].z * b.rows[1].x + a.rows[1].z * b.rows[1].y + a.rows[2].z * b.rows[1].z + a.rows[3].z * b.rows[1].w;
	result.rows[1].w = a.rows[0].w * b.rows[1].x + a.rows[1].w * b.rows[1].y + a.rows[2].w * b.rows[1].z + a.rows[3].w * b.rows[1].w;
	result.rows[2].x = a.rows[0].x * b.rows[2].x + a.rows[1].x * b.rows[2].y + a.rows[2].x * b.rows[2].z + a.rows[3].x * b.rows[2].w;
	result.rows[2].y = a.rows[0].y * b.rows[2].x + a.rows[1].y * b.rows[2].y + a.rows[2].y * b.rows[2].z + a.rows[3].y * b.rows[2].w;
	result.rows[2].z = a.rows[0].z * b.rows[2].x + a.rows[1].z * b.rows[2].y + a.rows[2].z * b.rows[2].z + a.rows[3].z * b.rows[2].w;
	result.rows[2].w = a.rows[0].w * b.rows[2].x + a.rows[1].w * b.rows[2].y + a.rows[2].w * b.rows[2].z + a.rows[3].w * b.rows[2].w;
	result.rows[3].x = a.rows[3].x;
	result.rows[3].y = a.rows[3].y;
	result.rows[3].z = a.rows[3].z;
	result.rows[3].w = a.rows[3].w;

	return result;
}

mat4 mat4_transpose(mat4 matrix)
{
	mat4 result = { 0 };
	result.rows[0].x = matrix.rows[0].x;
	result.rows[0].y = matrix.rows[1].x;
	result.rows[0].z = matrix.rows[2].x;
	result.rows[0].w = matrix.rows[3].x;
	result.rows[1].x = matrix.rows[0].y;
	result.rows[1].y = matrix.rows[1].y;
	result.rows[1].z = matrix.rows[2].y;
	result.rows[1].w = matrix.rows[3].y;
	result.rows[2].x = matrix.rows[0].z;
	result.rows[2].y = matrix.rows[1].z;
	result.rows[2].z = matrix.rows[2].z;
	result.rows[2].w = matrix.rows[3].z;
	result.rows[3].x = matrix.rows[0].w;
	result.rows[3].y = matrix.rows[1].w;
	result.rows[3].z = matrix.rows[2].w;
	result.rows[3].w = matrix.rows[3].w;

	return result;
}

mat4 mat4_scale(mat4 matrix, float scale)
{
	matrix.rows[0] = vec4_scale(matrix.rows[0], scale);
	matrix.rows[1] = vec4_scale(matrix.rows[1], scale);
	matrix.rows[2] = vec4_scale(matrix.rows[2], scale);
	matrix.rows[3] = vec4_scale(matrix.rows[3], scale);

	return matrix;
}
