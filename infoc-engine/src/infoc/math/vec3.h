#pragma once

#include "infoc/core/defines.h"

#include <math.h>

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

inline vec3 vec3_create(float x, float y, float z)
{
	vec3 vector = { x, y, z };
	return vector;
}

inline vec3 vec3_scalar(float scalar)
{
	vec3 vector = { scalar, scalar, scalar };
	return vector;
}

inline vec3 vec3_vec3(vec3 other)
{
	vec3 vector = { other.x, other.y, other.z };
	return vector;
}

inline vec3 vec3_add(vec3 a, vec3 b)
{
	vec3 result = { a.x + b.x, a.y + b.y, a.z + b.z };
	return result;
}

inline vec3 vec3_sub(vec3 a, vec3 b)
{
	vec3 result = { a.x - b.x, a.y - b.y, a.z - b.z };
	return result;
}

inline vec3 vec3_scale(vec3 a, float scalar)
{
	vec3 result = { a.x * scalar, a.y * scalar, a.z * scalar };
	return result;
}

inline vec3 vec3_mul(vec3 a, vec3 b)
{
	vec3 result = { a.x * b.x, a.y * b.y, a.z * b.z };
	return result;
}

inline float vec3_dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 vec3_cross(vec3 a, vec3 b)
{
	vec3 result = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
	return result;
}

inline float vec3_length_squared(vec3 vector)
{
	return vec3_dot(vector, vector);
}

inline float vec3_length(vec3 vector)
{
	return sqrtf(vec3_length_squared(vector));
}

inline vec3 vec3_normalise(vec3 vector)
{
	float length = vec3_length(vector);
	vec3 result = { vector.x / length, vector.y / length, vector.z / length };
	return result;
}

inline bool vec3_eq(vec3 a, vec3 b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
