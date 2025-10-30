#pragma once

#include "infoc/core/defines.h"

typedef struct vec4
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
	union
	{
		float w;
		float a;
		float q;
	};
} vec4;

vec4 vec4_create(float x, float y, float z, float w);
vec4 vec4_scalar(float scalar);
vec4 vec4_vec4(vec4 other);

vec4 vec4_add(vec4 a, vec4 b);
vec4 vec4_sub(vec4 a, vec4 b);

vec4 vec4_scale(vec4 a, float scalar);
vec4 vec4_mul(vec4 a, vec4 b);

float vec4_dot(vec4 a, vec4 b);

float vec4_length_squared(vec4 vector);
float vec4_length(vec4 vector);

vec4 vec4_normalise(vec4 vector);

bool vec4_eq(vec4 a, vec4 b);
