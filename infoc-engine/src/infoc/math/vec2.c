#include "vec2.h"

#include <math.h>

vec2 vec2_create(float x, float y)
{
	vec2 vector = { 0 };
	vector.x = x;
	vector.y = y;
	return vector;
}

vec2 vec2_scalar(float scalar)
{
	return vec2_create(scalar, scalar);
}

vec2 vec2_vec2(vec2 other)
{
	return vec2_create(other.x, other.y);
}

vec2 vec2_add(vec2 a, vec2 b)
{
	return vec2_create(a.x + b.x, a.y + b.y);
}

vec2 vec2_sub(vec2 a, vec2 b)
{
	return vec2_create(a.x - b.x, a.y - b.y);
}

vec2 vec2_scale(vec2 a, float scalar)
{
	return vec2_create(a.x * scalar, a.y * scalar);
}

vec2 vec2_mul(vec2 a, vec2 b)
{
	return vec2_create(a.x * b.x, a.y * b.y);
}

float vec2_dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

float vec2_cross(vec2 a, vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

float vec2_length_squared(vec2 vector)
{
	return vec2_dot(vector, vector);
}

float vec2_length(vec2 vector)
{
	return sqrtf(vec2_length_squared(vector));
}

vec2 vec2_normalise(vec2 vector)
{
	float length = vec2_length(vector);
	return vec2_scale(vector, 1.0f / length);
}

bool vec2_eq(vec2 a, vec2 b)
{
	return fabs(a.x - b.x) < 0.001f && fabs(a.y - b.y) < 0.001f;
}
