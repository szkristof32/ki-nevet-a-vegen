#include "vec4.h"

#include <math.h>

vec4 vec4_create(float x, float y, float z, float w)
{
	vec4 vector = { 0 };
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = w;
	return vector;
}

vec4 vec4_scalar(float scalar)
{
	return vec4_create(scalar, scalar, scalar, scalar);
}

vec4 vec4_vec4(vec4 other)
{
	return vec4_create(other.x, other.y, other.z, other.w);
}

vec4 vec4_add(vec4 a, vec4 b)
{
	return vec4_create(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

vec4 vec4_sub(vec4 a, vec4 b)
{
	return vec4_create(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

vec4 vec4_scale(vec4 a, float scalar)
{
	return vec4_create(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);
}

vec4 vec4_mul(vec4 a, vec4 b)
{
	return vec4_create(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

float vec4_dot(vec4 a, vec4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float vec4_length_squared(vec4 vector)
{
	return vec4_dot(vector, vector);
}

float vec4_length(vec4 vector)
{
	return sqrtf(vec4_length_squared(vector));
}

vec4 vec4_normalise(vec4 vector)
{
	float length = vec4_length(vector);
	return vec4_scale(vector, 1.0f / length);
}

bool vec4_eq(vec4 a, vec4 b)
{
	return fabs(a.x - b.x) < 0.001f && fabs(a.y - b.y) < 0.001f && fabs(a.z - b.z) < 0.001f && fabs(a.w - b.w) < 0.001f;
}

vec4 vec4_min(vec4 a, vec4 b)
{
	return vec4_create(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w));
}

vec4 vec4_max(vec4 a, vec4 b)
{
	return vec4_create(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w));
}
