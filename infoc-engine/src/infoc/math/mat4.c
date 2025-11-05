#include "mat4.h"

mat4 mat4_identity()
{
	mat4 result = { 0 };
	result.values[0][0] = 1.0f;
	result.values[1][1] = 1.0f;
	result.values[2][2] = 1.0f;
	result.values[3][3] = 1.0f;
	return result;
}

mat4 mat4_mul(mat4 mat1, mat4 mat2)
{
	float a1 = mat1.a, b1 = mat1.b, c1 = mat1.c, d1 = mat1.d, 
		e1 = mat1.e, f1 = mat1.f, g1 = mat1.g, h1 = mat1.h,
		i1 = mat1.i, j1 = mat1.j, k1 = mat1.k, l1 = mat1.l,
		m1 = mat1.m, n1 = mat1.n, o1 = mat1.o, p1 = mat1.p;
	float a2 = mat2.a, b2 = mat2.b, c2 = mat2.c, d2 = mat2.d,
		e2 = mat2.e, f2 = mat2.f, g2 = mat2.g, h2 = mat2.h,
		i2 = mat2.i, j2 = mat2.j, k2 = mat2.k, l2 = mat2.l,
		m2 = mat2.m, n2 = mat2.n, o2 = mat2.o, p2 = mat2.p;

	mat4 result = { 0 };
	result.a = a1 * a2 + e1 * b2 + i1 * c2 + m1 * d2;
	result.b = b1 * a2 + f1 * b2 + j1 * c2 + n1 * d2;
	result.c = c1 * a2 + g1 * b2 + k1 * c2 + o1 * d2;
	result.d = d1 * a2 + h1 * b2 + l1 * c2 + p1 * d2;
	result.e = a1 * e2 + e1 * f2 + i1 * g2 + m1 * h2;
	result.f = b1 * e2 + f1 * f2 + j1 * g2 + n1 * h2;
	result.g = c1 * e2 + g1 * f2 + k1 * g2 + o1 * h2;
	result.h = d1 * e2 + h1 * f2 + l1 * g2 + p1 * h2;
	result.i = a1 * i2 + e1 * j2 + i1 * k2 + m1 * l2;
	result.j = b1 * i2 + f1 * j2 + j1 * k2 + n1 * l2;
	result.k = c1 * i2 + g1 * j2 + k1 * k2 + o1 * l2;
	result.l = d1 * i2 + h1 * j2 + l1 * k2 + p1 * l2;
	result.m = a1 * m2 + e1 * n2 + i1 * o2 + m1 * p2;
	result.n = b1 * m2 + f1 * n2 + j1 * o2 + n1 * p2;
	result.o = c1 * m2 + g1 * n2 + k1 * o2 + o1 * p2;
	result.p = d1 * m2 + h1 * n2 + l1 * o2 + p1 * p2;

	return result;
}

mat4 mat4_mul_rot(mat4 mat1, mat4 mat2)
{
	mat4 result = mat4_mul(mat1, mat2);
	result.rows[3] = mat1.rows[3];

	return result;
}

mat4 mat4_transpose(mat4 matrix)
{
	mat4 result = { 0 };
	result.values[0][0] = matrix.values[0][0];
	result.values[0][1] = matrix.values[1][0];
	result.values[0][2] = matrix.values[2][0];
	result.values[0][3] = matrix.values[3][0];
	result.values[1][0] = matrix.values[0][1];
	result.values[1][1] = matrix.values[1][1];
	result.values[1][2] = matrix.values[2][1];
	result.values[1][3] = matrix.values[3][1];
	result.values[2][0] = matrix.values[0][2];
	result.values[2][1] = matrix.values[1][2];
	result.values[2][2] = matrix.values[2][2];
	result.values[2][3] = matrix.values[3][2];
	result.values[3][0] = matrix.values[0][3];
	result.values[3][1] = matrix.values[1][3];
	result.values[3][2] = matrix.values[2][3];
	result.values[3][3] = matrix.values[3][3];

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
	float a = matrix.a, b = matrix.b, c = matrix.c, d = matrix.d,
		e = matrix.e, f = matrix.f, g = matrix.g, h = matrix.h, 
		i = matrix.i, j = matrix.j, k = matrix.k, l = matrix.l, 
		m = matrix.m, n = matrix.n, o = matrix.o, p = matrix.p;

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
	result.values[0][0] = (f * c1 - g * c5 + h * c9) * idt;
	result.values[0][1] = (b * c1 - c * c5 + d * c9) * ndt;
	result.values[0][2] = (n * c2 - o * c6 + p * c10) * idt;
	result.values[0][3] = (j * c2 - k * c6 + l * c10) * ndt;
	result.values[1][0] = (e * c1 - g * c3 + h * c11) * ndt;
	result.values[1][1] = (a * c1 - c * c3 + d * c11) * idt;
	result.values[1][2] = (m * c2 - o * c4 + p * c12) * ndt;
	result.values[1][3] = (i * c2 - k * c4 + l * c12) * idt;
	result.values[2][0] = (e * c5 - f * c3 + h * c7) * idt;
	result.values[2][1] = (a * c5 - b * c3 + d * c7) * ndt;
	result.values[2][2] = (m * c6 - n * c4 + p * c8) * idt;
	result.values[2][3] = (i * c6 - j * c4 + l * c8) * ndt;
	result.values[3][0] = (e * c9 - f * c11 + g * c7) * ndt;
	result.values[3][1] = (a * c9 - b * c11 + c * c7) * idt;
	result.values[3][2] = (m * c10 - n * c12 + o * c8) * ndt;
	result.values[3][3] = (i * c10 - j * c12 + k * c8) * idt;

	return result;
}

bool mat4_eq(mat4 a, mat4 b)
{
	return vec4_eq(a.rows[0], b.rows[0]) && vec4_eq(a.rows[1], b.rows[1]) && vec4_eq(a.rows[2], b.rows[2]) && vec4_eq(a.rows[3], b.rows[3]);
}
