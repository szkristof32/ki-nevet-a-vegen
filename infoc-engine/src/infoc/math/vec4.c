#include "vec4.h"

#include <math.h>

vec4 vec4_create(float x, float y, float z, float w)
{
	vec4 vector = { x, y, z, w };
	return vector;
}

vec4 vec4_scalar(float scalar)
{
	vec4 vector = { scalar, scalar, scalar, scalar };
	return vector;
}

vec4 vec4_vec4(vec4 other)
{
	vec4 vector = { other.x, other.y, other.z, other.w };
	return vector;
}

vec4 vec4_add(vec4 a, vec4 b)
{
	vec4 result = { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
	return result;
}

vec4 vec4_sub(vec4 a, vec4 b)
{
	vec4 result = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return result;
}

vec4 vec4_scale(vec4 a, float scalar)
{
	vec4 result = { a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar };
	return result;
}

vec4 vec4_mul(vec4 a, vec4 b)
{
	vec4 result = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
	return result;
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
	vec4 result = { vector.x / length, vector.y / length, vector.z / length, vector.w / length };
	return result;
}

bool vec4_eq(vec4 a, vec4 b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
