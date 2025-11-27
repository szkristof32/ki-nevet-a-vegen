#pragma once

#include "infoc/core/defines.h"

/**
 * Three component vector
 */
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

/**
 * Creates a three component vector
 *
 * @param x X coordinate of the vector
 * @param y Y coordinate of the vector
 * @param z Z coordinate of the vector
 *
 * @returns The vector (x;y;z)
 */
vec3 vec3_create(float x, float y, float z);
/**
 * Creates a three component vector
 *
 * @param scalar The x, y and z coordinates of the vector
 *
 * @returns The vector (scalar;scalar;scalar)
 */
vec3 vec3_scalar(float scalar);
/**
 * Creates a three component vector
 *
 * @param other Source vector
 *
 * @returns The vector (other.x;other.y;other.z)
 */
vec3 vec3_vec3(vec3 other);

/**
 * Adds together two vectors
 *
 * @param a, b Addition operands
 *
 * @returns The sum of a and b
 */
vec3 vec3_add(vec3 a, vec3 b);
/**
 * Subtracts a vector from the other
 *
 * @param a Minuend vector
 * @param b Subtrahend vector
 *
 * @returns The difference of a and b
 */
vec3 vec3_sub(vec3 a, vec3 b);

/**
 * Scales a vector by a scalar value
 *
 * @param a Source vector
 * @param scalar The scalar to multiply with
 *
 * @returns The scaled vector
 */
vec3 vec3_scale(vec3 a, float scalar);
/**
 * Multiplies two vectors per component resulting in (a.x*b.x;a.y*b.y;a.z*b.z)
 *
 * @param a, b The operands of the multiplication
 *
 * @returns The product
 */
vec3 vec3_mul(vec3 a, vec3 b);
/**
 * Raises each component of the vector to the second power
 *
 * @param vector Vector subject to squaring
 *
 * @returns The resulting vector
 */
vec3 vec3_square(vec3 vector);
/**
 * Inverts each component of the vector
 *
 * @param vector Vector to be inverted
 *
 * @returns The inverted vector
 */
vec3 vec3_inv(vec3 vector);

/**
 * Calculates the dot product of two vectors
 *
 * @param a, b Two vectors
 *
 * @returns The dot product of a and b
 */
float vec3_dot(vec3 a, vec3 b);
/**
 * Calculates the cross product of two vectors
 *
 * @param a, b Two vectors
 *
 * @returns The cross product of a and b
 */
vec3 vec3_cross(vec3 a, vec3 b);

/**
 * Calculates the length of the vector raised to the second power
 *
 * @param vector The vector whose length is to be calculated
 *
 * @returns The length squared
 */
float vec3_length_squared(vec3 vector);
/**
 * Calculates the length of the vector
 *
 * @param vector The vector whose length is to be calculated
 *
 * @returns The length
 */
float vec3_length(vec3 vector);

/**
 * Normalises the vector
 *
 * @param vector The vector which needs to be normalised
 *
 * @returns The normalised vector
 */
vec3 vec3_normalise(vec3 vector);

/**
 * Determines if two vectors are equal
 *
 * @param a, b The vectors to be checked
 *
 * @returns A boolean indicating if they are equal
 */
bool vec3_eq(vec3 a, vec3 b);
