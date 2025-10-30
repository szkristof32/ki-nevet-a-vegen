#include "mat4.h"

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

mat4 mat4_invert(mat4 matrix)
{
	float a = matrix.rows[0].x;
	float b = matrix.rows[0].y;
	float c = matrix.rows[0].z;
	float d = matrix.rows[0].w;
	float e = matrix.rows[1].x;
	float f = matrix.rows[1].y;
	float g = matrix.rows[1].z;
	float h = matrix.rows[1].w;
	float i = matrix.rows[2].x;
	float j = matrix.rows[2].y;
	float k = matrix.rows[2].z;
	float l = matrix.rows[2].w;
	float m = matrix.rows[3].x;
	float n = matrix.rows[3].y;
	float o = matrix.rows[3].z;
	float p = matrix.rows[3].w;

	float c1 = k * p - l * o;
	float c2 = c * h - d * g;
	float c3 = i * p - l * m;
	float c4 = a * h - d * e;
	float c5 = j * p - l * n;
	float c6 = b * h - d * f;
	float c7 = i * n - j * m;
	float c8 = a * f - b * e;
	float c9 = j * o - k * n;
	float c10 = b * g - c * f;
	float c11 = i * o - k * m;
	float c12 = a * g - c * e;

	float idt = 1.0f / (c8 * c1 + c4 * c9 + c10 * c3 + c2 * c7 - c12 * c5 - c6 * c11);
	float ndt = -idt;

	mat4 result = { 0 };
	result.rows[0].x = (f * c1 - g * c5 + h * c9) * idt;
	result.rows[0].y = (b * c1 - c * c5 + d * c9) * ndt;
	result.rows[0].z = (n * c2 - o * c6 + p * c10) * idt;
	result.rows[0].w = (j * c2 - k * c6 + l * c10) * ndt;
	result.rows[1].x = (e * c1 - g * c3 + h * c11) * ndt;
	result.rows[1].y = (a * c1 - c * c3 + d * c11) * idt;
	result.rows[1].z = (m * c2 - o * c4 + p * c12) * ndt;
	result.rows[1].w = (i * c2 - k * c4 + l * c12) * idt;
	result.rows[2].x = (e * c5 - f * c3 + h * c7) * idt;
	result.rows[2].y = (a * c5 - b * c3 + d * c7) * ndt;
	result.rows[2].z = (m * c6 - n * c4 + p * c8) * idt;
	result.rows[2].w = (i * c6 - j * c4 + l * c8) * ndt;
	result.rows[3].x = (e * c9 - f * c11 + g * c7) * ndt;
	result.rows[3].y = (a * c9 - b * c11 + c * c7) * idt;
	result.rows[3].z = (m * c10 - n * c12 + o * c8) * ndt;
	result.rows[3].w = (i * c10 - j * c12 + k * c8) * idt;

	return result;
}

bool mat4_eq(mat4 a, mat4 b)
{
	return vec4_eq(a.rows[0], b.rows[0]) && vec4_eq(a.rows[1], b.rows[1]) && vec4_eq(a.rows[2], b.rows[2]) && vec4_eq(a.rows[3], b.rows[3]);
}
