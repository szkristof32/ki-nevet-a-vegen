#pragma once

#include "infoc/core/defines.h"

#include <math.h>

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

static inline vec2 vec2_create(float x, float y)
{
	vec2 vector = { 0 };
	vector.x = x;
	vector.y = y;
	return vector;
}

static inline vec2 vec2_scalar(float scalar)
{
	return vec2_create(scalar, scalar);
}

static inline vec2 vec2_vec2(vec2 other)
{
	return vec2_create(other.x, other.y);
}

static inline vec2 vec2_add(vec2 a, vec2 b)
{
	return vec2_create(a.x + b.x, a.y + b.y);
}

static inline vec2 vec2_sub(vec2 a, vec2 b)
{
	return vec2_create(a.x - b.x, a.y - b.y);
}

static inline vec2 vec2_scale(vec2 a, float scalar)
{
	return vec2_create(a.x * scalar, a.y * scalar);
}

static inline vec2 vec2_mul(vec2 a, vec2 b)
{
	return vec2_create(a.x * b.x, a.y * b.y);
}

static inline float vec2_dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

static inline float vec2_cross(vec2 a, vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

static inline float vec2_length_squared(vec2 vector)
{
	return vec2_dot(vector, vector);
}

static inline float vec2_length(vec2 vector)
{
	return sqrtf(vec2_length_squared(vector));
}

static inline vec2 vec2_normalise(vec2 vector)
{
	float length = vec2_length(vector);
	return vec2_scale(vector, 1.0f / length);
}

static inline bool vec2_eq(vec2 a, vec2 b)
{
	return a.x == b.x && a.y == b.y;
}
