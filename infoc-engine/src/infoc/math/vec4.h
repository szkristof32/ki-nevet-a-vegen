#pragma once

#include "infoc/core/defines.h"

#include <math.h>

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

static inline vec4 vec4_create(float x, float y, float z, float w)
{
	vec4 vector = { 0 };
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

static inline vec4 vec4_scalar(float scalar)
{
	return vec4_create(scalar, scalar, scalar, scalar);
}

static inline vec4 vec4_vec4(vec4 other)
{
	return vec4_create(other.x, other.y, other.z, other.w);
}

static inline vec4 vec4_add(vec4 a, vec4 b)
{
	return vec4_create(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

static inline vec4 vec4_sub(vec4 a, vec4 b)
{
	return vec4_create(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

static inline vec4 vec4_scale(vec4 a, float scalar)
{
	return vec4_create(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);
}

static inline vec4 vec4_mul(vec4 a, vec4 b)
{
	return vec4_create(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

static inline float vec4_dot(vec4 a, vec4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

static inline float vec4_length_squared(vec4 vector)
{
	return vec4_dot(vector, vector);
}

static inline float vec4_length(vec4 vector)
{
	return sqrtf(vec4_length_squared(vector));
}

static inline vec4 vec4_normalise(vec4 vector)
{
	float length = vec4_length(vector);
	return vec4_scale(vector, 1.0f / length);
}

static inline bool vec4_eq(vec4 a, vec4 b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
