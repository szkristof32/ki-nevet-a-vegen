#pragma once

#include "vec3.h"

typedef struct mat3
{
	union
	{
		vec3 rows[3];
		float values[3][3];
		struct
		{
			float a, b, c;
			float d, e, f;
			float g, h, i;
		};
	};
} mat3;

mat3 mat3_identity();

mat3 mat3_mul(mat3 mat1, mat3 mat2);

mat3 mat3_transpose(mat3 matrix);

mat3 mat3_scale(mat3 matrix, float scale);

mat3 mat3_invert(mat3 matrix);

bool mat3_eq(mat3 a, mat3 b);
