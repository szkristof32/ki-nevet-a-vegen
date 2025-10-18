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

inline vec2 vec2_create(float x, float y)
{
	vec2 vector = { x, y };
	return vector;
}

inline vec2 vec2_scalar(float scalar)
{
	vec2 vector = { scalar, scalar };
	return vector;
}

inline vec2 vec2_vec2(vec2 other)
{
	vec2 vector = { other.x, other.y };
	return vector;
}

inline vec2 vec2_add(vec2 a, vec2 b)
{
	vec2 result = { a.x + b.x, a.y + b.y };
	return result;
}

inline vec2 vec2_sub(vec2 a, vec2 b)
{
	vec2 result = { a.x - b.x, a.y - b.y };
	return result;
}

inline vec2 vec2_scale(vec2 a, float scalar)
{
	vec2 result = { a.x * scalar, a.y * scalar };
	return result;
}

inline vec2 vec2_mul(vec2 a, vec2 b)
{
	vec2 result = { a.x * b.x, a.y * b.y };
	return result;
}

inline float vec2_dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

inline float vec2_cross(vec2 a, vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

inline float vec2_length_squared(vec2 vector)
{
	return vec2_dot(vector, vector);
}

inline float vec2_length(vec2 vector)
{
	return sqrtf(vec2_length_squared(vector));
}

inline vec2 vec2_normalise(vec2 vector)
{
	float length = vec2_length(vector);
	vec2 result = { vector.x / length, vector.y / length };
	return result;
}

inline bool vec2_eq(vec2 a, vec2 b)
{
	return a.x == b.x && a.y == b.y;
}
