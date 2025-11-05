#pragma once

#include "vec4.h"

typedef struct mat4
{
	union
	{
		vec4 rows[4];
		float values[4][4];
		struct
		{
			float a, b, c, d;
			float e, f, g, h;
			float i, j, k, l;
			float m, n, o, p;
		};
	};
} mat4;

mat4 mat4_identity();

mat4 mat4_mul(mat4 mat1, mat4 mat2);

mat4 mat4_mul_rot(mat4 mat1, mat4 mat2);

mat4 mat4_transpose(mat4 matrix);

mat4 mat4_scale(mat4 matrix, float scale);

mat4 mat4_invert(mat4 matrix);

bool mat4_eq(mat4 a, mat4 b);
