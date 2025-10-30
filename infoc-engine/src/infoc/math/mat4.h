#pragma once

#include "vec4.h"

typedef struct mat4
{
	vec4 rows[4];
} mat4;

mat4 mat4_identity();

mat4 mat4_mul(mat4 a, mat4 b);

mat4 mat4_mul_rot(mat4 a, mat4 b);

mat4 mat4_transpose(mat4 matrix);

mat4 mat4_scale(mat4 matrix, float scale);

mat4 mat4_invert(mat4 matrix);

bool mat4_eq(mat4 a, mat4 b);
