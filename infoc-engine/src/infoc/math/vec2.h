#pragma once

#include "infoc/core/defines.h"

typedef struct vec2
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
} vec2;

vec2 vec2_create(float x, float y);
vec2 vec2_scalar(float scalar);
vec2 vec2_vec2(vec2 other);

vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);

vec2 vec2_scale(vec2 a, float scalar);
vec2 vec2_mul(vec2 a, vec2 b);

float vec2_dot(vec2 a, vec2 b);
float vec2_cross(vec2 a, vec2 b);

float vec2_length_squared(vec2 vector);
float vec2_length(vec2 vector);

vec2 vec2_normalise(vec2 vector);

bool vec2_eq(vec2 a, vec2 b);
