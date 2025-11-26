#pragma once

#include "infoc/core/defines.h"

/*
* Four component vector
*/
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

/*
* Creates a four component vector
*
* @param x X coordinate of the vector
* @param y Y coordinate of the vector
* @param z Z coordinate of the vector
* @param w W coordinate of the vector
*
* @returns The vector (x;y;z;w)
*/
vec4 vec4_create(float x, float y, float z, float w);
/*
* Creates a four component vector
*
* @param scalar The x, y, z and w coordinates of the vector
*
* @returns The vector (scalar;scalar;scalar;scalar)
*/
vec4 vec4_scalar(float scalar);
/*
* Creates a four component vector
*
* @param other Source vector
*
* @returns The vector (other.x;other.y;other.z;other.w)
*/
vec4 vec4_vec4(vec4 other);

/*
* Adds together two vectors
*
* @param a, b Addition operands
*
* @returns The sum of a and b
*/
vec4 vec4_add(vec4 a, vec4 b);
/*
* Subtracts a vector from the other
*
* @param a Minuend vector
* @param b Subtrahend vector
*
* @returns The difference of a and b
*/
vec4 vec4_sub(vec4 a, vec4 b);

/*
* Scales a vector by a scalar value
*
* @param a Source vector
* @param scalar The scalar to multiply with
*
* @returns The scaled vector
*/
vec4 vec4_scale(vec4 a, float scalar);
/*
* Multiplies two vectors per component resulting in (a.x*b.x;a.y*b.y;a.z*b.z;a.w*b.w)
*
* @param a, b The operands of the multiplication
*
* @returns The product
*/
vec4 vec4_mul(vec4 a, vec4 b);

/*
* Calculates the dot product of two vectors
*
* @param a, b Two vectors
*
* @returns The dot product of a and b
*/
float vec4_dot(vec4 a, vec4 b);

/*
* Calculates the length of the vector raised to the second power
*
* @param vector The vector whose length is to be calculated
*
* @returns The length squared
*/
float vec4_length_squared(vec4 vector);
/*
* Calculates the length of the vector
*
* @param vector The vector whose length is to be calculated
*
* @returns The length
*/
float vec4_length(vec4 vector);

/*
* Normalises the vector
*
* @param vector The vector which needs to be normalised
*
* @returns The normalised vector
*/
vec4 vec4_normalise(vec4 vector);

/*
* Determines if two vectors are equal
*
* @param a, b The vectors to be checked
*
* @returns A boolean indicating if they are equal
*/
bool vec4_eq(vec4 a, vec4 b);

vec4 vec4_min(vec4 a, vec4 b);
vec4 vec4_max(vec4 a, vec4 b);
