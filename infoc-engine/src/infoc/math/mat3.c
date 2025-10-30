#include "mat3.h"

mat3 mat3_identity()
{
	mat3 result = { 0 };
	result.rows[0].x = 1.0f;
	result.rows[1].y = 1.0f;
	result.rows[2].z = 1.0f;
	return result;
}

mat3 mat3_mul(mat3 a, mat3 b)
{
	mat3 result = { 0 };
	result.rows[0].x = a.rows[0].x * b.rows[0].x + a.rows[1].x * b.rows[0].y + a.rows[2].x * b.rows[0].z;
	result.rows[0].y = a.rows[0].y * b.rows[0].x + a.rows[1].y * b.rows[0].y + a.rows[2].y * b.rows[0].z;
	result.rows[0].z = a.rows[0].z * b.rows[0].x + a.rows[1].z * b.rows[0].y + a.rows[2].z * b.rows[0].z;
	result.rows[1].x = a.rows[0].x * b.rows[1].x + a.rows[1].x * b.rows[1].y + a.rows[2].x * b.rows[1].z;
	result.rows[1].y = a.rows[0].y * b.rows[1].x + a.rows[1].y * b.rows[1].y + a.rows[2].y * b.rows[1].z;
	result.rows[1].z = a.rows[0].z * b.rows[1].x + a.rows[1].z * b.rows[1].y + a.rows[2].z * b.rows[1].z;
	result.rows[2].x = a.rows[0].x * b.rows[2].x + a.rows[1].x * b.rows[2].y + a.rows[2].x * b.rows[2].z;
	result.rows[2].y = a.rows[0].y * b.rows[2].x + a.rows[1].y * b.rows[2].y + a.rows[2].y * b.rows[2].z;
	result.rows[2].z = a.rows[0].z * b.rows[2].x + a.rows[1].z * b.rows[2].y + a.rows[2].z * b.rows[2].z;

	return result;
}

mat3 mat3_transpose(mat3 matrix)
{
	mat3 result = { 0 };
	result.rows[0].x = matrix.rows[0].x;
	result.rows[0].y = matrix.rows[1].x;
	result.rows[0].z = matrix.rows[2].x;
	result.rows[1].x = matrix.rows[0].y;
	result.rows[1].y = matrix.rows[1].y;
	result.rows[1].z = matrix.rows[2].y;
	result.rows[2].x = matrix.rows[0].z;
	result.rows[2].y = matrix.rows[1].z;
	result.rows[2].z = matrix.rows[2].z;

	return result;
}

mat3 mat3_scale(mat3 matrix, float scale)
{
	matrix.rows[0] = vec3_scale(matrix.rows[0], scale);
	matrix.rows[1] = vec3_scale(matrix.rows[1], scale);
	matrix.rows[2] = vec3_scale(matrix.rows[2], scale);

	return matrix;
}

mat3 mat3_invert(mat3 matrix)
{
	float c1 = matrix.rows[1].y * matrix.rows[2].z - matrix.rows[1].z * matrix.rows[2].y;
	float c2 = matrix.rows[1].x * matrix.rows[2].z - matrix.rows[2].x * matrix.rows[1].z;
	float c3 = matrix.rows[1].x * matrix.rows[2].y - matrix.rows[2].x * matrix.rows[1].y;
	float idt = 1.0f / (matrix.rows[0].x * c1 - matrix.rows[0].y * c2 + matrix.rows[0].z * c3);
	float ndt = -idt;

	mat3 result = { 0 };
	result.rows[0].x = idt * c1;
	result.rows[0].y = ndt * (matrix.rows[1].y * matrix.rows[2].z - matrix.rows[2].y * matrix.rows[0].z);
	result.rows[0].z = idt * (matrix.rows[1].y * matrix.rows[1].z - matrix.rows[1].y * matrix.rows[0].z);
	result.rows[1].x = ndt * c2;
	result.rows[1].y = idt * (matrix.rows[0].x * matrix.rows[2].z - matrix.rows[2].x * matrix.rows[0].z);
	result.rows[1].z = ndt * (matrix.rows[0].x * matrix.rows[1].z - matrix.rows[1].x * matrix.rows[0].z);
	result.rows[2].x = idt * c3;
	result.rows[2].y = ndt * (matrix.rows[0].x * matrix.rows[2].y - matrix.rows[2].x * matrix.rows[0].y);
	result.rows[2].z = idt * (matrix.rows[0].x * matrix.rows[1].y - matrix.rows[1].x * matrix.rows[0].y);

	return result;
}

bool mat3_eq(mat3 a, mat3 b)
{
	return vec3_eq(a.rows[0], b.rows[0]) && vec3_eq(a.rows[1], b.rows[1]) && vec3_eq(a.rows[2], b.rows[2]);
}
