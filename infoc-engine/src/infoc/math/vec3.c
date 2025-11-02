#include "vec3.h"

#include <math.h>

vec3 vec3_create(float x, float y, float z)
{
	vec3 vector = { x, y, z };
	return vector;
}

vec3 vec3_scalar(float scalar)
{
	vec3 vector = { scalar, scalar, scalar };
	return vector;
}

vec3 vec3_vec3(vec3 other)
{
	vec3 vector = { other.x, other.y, other.z };
	return vector;
}

vec3 vec3_add(vec3 a, vec3 b)
{
	vec3 result = { a.x + b.x, a.y + b.y, a.z + b.z };
	return result;
}

vec3 vec3_sub(vec3 a, vec3 b)
{
	vec3 result = { a.x - b.x, a.y - b.y, a.z - b.z };
	return result;
}

vec3 vec3_scale(vec3 a, float scalar)
{
	vec3 result = { a.x * scalar, a.y * scalar, a.z * scalar };
	return result;
}

vec3 vec3_mul(vec3 a, vec3 b)
{
	vec3 result = { a.x * b.x, a.y * b.y, a.z * b.z };
	return result;
}

vec3 vec3_square(vec3 vector)
{
	return vec3_mul(vector, vector);
}

vec3 vec3_inv(vec3 vector)
{
	return vec3_create(1.0f / vector.x, 1.0f / vector.y, 1.0f / vector.z);
}

float vec3_dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3_cross(vec3 a, vec3 b)
{
	vec3 result = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
	return result;
}

float vec3_length_squared(vec3 vector)
{
	return vec3_dot(vector, vector);
}

float vec3_length(vec3 vector)
{
	return sqrtf(vec3_length_squared(vector));
}

vec3 vec3_normalise(vec3 vector)
{
	float length = vec3_length(vector);
	vec3 result = { vector.x / length, vector.y / length, vector.z / length };
	return result;
}

bool vec3_eq(vec3 a, vec3 b)
{
	return fabs(a.x - b.x) < 0.001f && fabs(a.y - b.y) < 0.001f && fabs(a.z - b.z) < 0.001f;
}
