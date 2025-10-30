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

static inline vec3 vec3_create(float x, float y, float z)
{
	vec3 vector = { 0 };
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}

static inline vec3 vec3_scalar(float scalar)
{
	return vec3_create(scalar, scalar, scalar);
}

static inline vec3 vec3_vec3(vec3 other)
{
	return vec3_create(other.x, other.y, other.z);
}

static inline vec3 vec3_add(vec3 a, vec3 b)
{
	return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}

static inline vec3 vec3_sub(vec3 a, vec3 b)
{
	return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}

static inline vec3 vec3_scale(vec3 a, float scalar)
{
	return vec3_create(a.x * scalar, a.y * scalar, a.z * scalar);
}

static inline vec3 vec3_mul(vec3 a, vec3 b)
{
	return vec3_create(a.x * b.x, a.y * b.y, a.z * b.z);
}

static inline float vec3_dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline vec3 vec3_cross(vec3 a, vec3 b)
{
	return vec3_create(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

static inline float vec3_length_squared(vec3 vector)
{
	return vec3_dot(vector, vector);
}

static inline float vec3_length(vec3 vector)
{
	return sqrtf(vec3_length_squared(vector));
}

static inline vec3 vec3_normalise(vec3 vector)
{
	float length = vec3_length(vector);
	return vec3_scale(vector, 1.0f / length);
}

static inline bool vec3_eq(vec3 a, vec3 b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
