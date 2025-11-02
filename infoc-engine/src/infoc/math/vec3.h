#pragma once

#include "infoc/core/defines.h"

typedef struct vec3
{
	union
	{
		float x;
		float r;
		float s;
	};
	union
	{
		float y;
		float g;
		float t;
	};
	union
	{
		float z;
		float b;
		float p;
	};
} vec3;

vec3 vec3_create(float x, float y, float z);
vec3 vec3_scalar(float scalar);
vec3 vec3_vec3(vec3 other);

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);

vec3 vec3_scale(vec3 a, float scalar);
vec3 vec3_mul(vec3 a, vec3 b);
vec3 vec3_square(vec3 vector);
vec3 vec3_inv(vec3 vector);

float vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);

float vec3_length_squared(vec3 vector);
float vec3_length(vec3 vector);

vec3 vec3_normalise(vec3 vector);

bool vec3_eq(vec3 a, vec3 b);
