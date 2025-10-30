#include "vec2.h"

#include <math.h>

vec2 vec2_create(float x, float y)
{
	vec2 vector = { x, y };
	return vector;
}

vec2 vec2_scalar(float scalar)
{
	vec2 vector = { scalar, scalar };
	return vector;
}

vec2 vec2_vec2(vec2 other)
{
	vec2 vector = { other.x, other.y };
	return vector;
}

vec2 vec2_add(vec2 a, vec2 b)
{
	vec2 result = { a.x + b.x, a.y + b.y };
	return result;
}

vec2 vec2_sub(vec2 a, vec2 b)
{
	vec2 result = { a.x - b.x, a.y - b.y };
	return result;
}

vec2 vec2_scale(vec2 a, float scalar)
{
	vec2 result = { a.x * scalar, a.y * scalar };
	return result;
}

vec2 vec2_mul(vec2 a, vec2 b)
{
	vec2 result = { a.x * b.x, a.y * b.y };
	return result;
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
	vec2 result = { vector.x / length, vector.y / length };
	return result;
}

bool vec2_eq(vec2 a, vec2 b)
{
	return a.x == b.x && a.y == b.y;
}
