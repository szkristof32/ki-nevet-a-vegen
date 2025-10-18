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

inline vec4 vec4_create(float x, float y, float z, float w)
{
	vec4 vector = { x, y, z, w };
	return vector;
}

inline vec4 vec4_scalar(float scalar)
{
	vec4 vector = { scalar, scalar, scalar, scalar };
	return vector;
}

inline vec4 vec4_vec4(vec4 other)
{
	vec4 vector = { other.x, other.y, other.z, other.w };
	return vector;
}

inline vec4 vec4_add(vec4 a, vec4 b)
{
	vec4 result = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
	return result;
}

inline vec4 vec4_sub(vec4 a, vec4 b)
{
	vec4 result = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return result;
}

inline vec4 vec4_scale(vec4 a, float scalar)
{
	vec4 result = { a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar };
	return result;
}

inline vec4 vec4_mul(vec4 a, vec4 b)
{
	vec4 result = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
	return result;
}

inline float vec4_dot(vec4 a, vec4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline float vec4_length_squared(vec4 vector)
{
	return vec4_dot(vector, vector);
}

inline float vec4_length(vec4 vector)
{
	return sqrtf(vec4_length_squared(vector));
}

inline vec4 vec4_normalise(vec4 vector)
{
	float length = vec4_length(vector);
	vec4 result = { vector.x / length, vector.y / length, vector.z / length, vector.w / length };
	return result;
}

inline bool vec4_eq(vec4 a, vec4 b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
