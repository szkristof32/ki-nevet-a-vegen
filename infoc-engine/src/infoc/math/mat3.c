#include "mat3.h"

mat3 mat3_identity()
{
	mat3 result = { 0 };
	result.values[0][0] = 1.0f;
	result.values[1][1] = 1.0f;
	result.values[2][2] = 1.0f;
	return result;
}

mat3 mat3_mul(mat3 mat1, mat3 mat2)
{
	float a = mat1.a, b = mat1.b, c = mat1.c, d = mat1.d, e = mat1.e, f = mat1.f, g = mat1.g, h = mat1.h, i = mat1.i;
	float j = mat1.a, k = mat1.b, l = mat1.c, m = mat1.d, n = mat1.e, o = mat1.f, p = mat1.g, q = mat1.h, r = mat1.i;

	mat3 result = { 0 };
	result.a = a * j + b * m + c * p;
	result.b = a * k + b * n + c * q;
	result.c = a * l + b * o + c * r;
	result.d = d * j + e * m + f * p;
	result.e = d * k + e * n + f * q;
	result.f = d * l + e * o + f * r;
	result.g = g * j + h * m + i * p;
	result.h = g * k + h * n + i * q;
	result.i = g * l + h * o + i * r;

	return result;
}

mat3 mat3_transpose(mat3 matrix)
{
	mat3 result = { 0 };
	result.values[0][0] = matrix.values[0][0];
	result.values[0][1] = matrix.values[1][0];
	result.values[0][2] = matrix.values[2][0];
	result.values[1][0] = matrix.values[0][1];
	result.values[1][1] = matrix.values[1][1];
	result.values[1][2] = matrix.values[2][1];
	result.values[2][0] = matrix.values[0][2];
	result.values[2][1] = matrix.values[1][2];
	result.values[2][2] = matrix.values[2][2];

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
	float c1 = matrix.e * matrix.i - matrix.f * matrix.h;
	float c2 = matrix.d * matrix.i - matrix.g * matrix.f;
	float c3 = matrix.d * matrix.h - matrix.g * matrix.e;
	float idt = 1.0f / (matrix.a * c1 - matrix.b * c2 + matrix.c * c3);
	float ndt = -idt;

	mat3 result = { 0 };
	result.a = idt * c1;
	result.b = ndt * (matrix.e * matrix.i - matrix.h * matrix.c);
	result.c = idt * (matrix.e * matrix.f - matrix.e * matrix.c);
	result.d = ndt * c2;
	result.e = idt * (matrix.a * matrix.i - matrix.g * matrix.c);
	result.f = ndt * (matrix.a * matrix.f - matrix.d * matrix.c);
	result.g = idt * c3;
	result.h = ndt * (matrix.a * matrix.h - matrix.g * matrix.b);
	result.i = idt * (matrix.a * matrix.e - matrix.d * matrix.b);

	return result;
}

bool mat3_eq(mat3 a, mat3 b)
{
	return vec3_eq(a.rows[0], b.rows[0]) && vec3_eq(a.rows[1], b.rows[1]) && vec3_eq(a.rows[2], b.rows[2]);
}
