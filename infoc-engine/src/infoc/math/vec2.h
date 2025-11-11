#pragma once

#include "infoc/core/defines.h"

/*
* Two component vector
*/
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

/*
* Creates a two component vector
*
* @param x X coordinate of the vector
* @param y Y coordinate of the vector
*
* @returns The vector (x;y)
*/
vec2 vec2_create(float x, float y);
/*
* Creates a two component vector
*
* @param scalar The x and y coordinates of the vector
*
* @returns The vector (scalar;scalar)
*/
vec2 vec2_scalar(float scalar);
/*
* Creates a two component vector
*
* @param other Source vector
*
* @returns The vector (other.x;other.y)
*/
vec2 vec2_vec2(vec2 other);

/*
* Adds together two vectors
*
* @param a, b Addition operands
*
* @returns The sum of a and b
*/
vec2 vec2_add(vec2 a, vec2 b);
/*
* Subtracts a vector from the other
*
* @param a Minuend vector
* @param b Subtrahend vector
*
* @returns The difference of a and b
*/
vec2 vec2_sub(vec2 a, vec2 b);

/*
* Scales a vector by a scalar value
*
* @param a Source vector
* @param scalar The scalar to multiply with
*
* @returns The scaled vector
*/
vec2 vec2_scale(vec2 a, float scalar);
/*
* Multiplies two vectors per component resulting in (a.x*b.x;a.y*b.y)
*
* @param a, b The operands of the multiplication
*
* @returns The product
*/
vec2 vec2_mul(vec2 a, vec2 b);

/*
* Calculates the dot product of two vectors
*
* @param a, b Two vectors
*
* @returns The dot product of a and b
*/
float vec2_dot(vec2 a, vec2 b);
/*
* Calculates the discriminant of the 2x2 matrix where the rows are a and b
*
* @param a, b The rows of the 2x2 matrix
*
* @returns The discriminant
*/
float vec2_cross(vec2 a, vec2 b);

/*
* Calculates the length of the vector raised to the second power
*
* @param vector The vector whose length is to be calculated
*
* @returns The length squared
*/
float vec2_length_squared(vec2 vector);
/*
* Calculates the length of the vector
*
* @param vector The vector whose length is to be calculated
*
* @returns The length
*/
float vec2_length(vec2 vector);

/*
* Normalises the vector
*
* @param vector The vector which needs to be normalised
*
* @returns The normalised vector
*/
vec2 vec2_normalise(vec2 vector);

/*
* Determines if two vectors are equal
*
* @param a, b The vectors to be checked
*
* @returns A boolean indicating if they are equal
*/
bool vec2_eq(vec2 a, vec2 b);
