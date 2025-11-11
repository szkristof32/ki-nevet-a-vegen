#pragma once

#include "vec3.h"

/*
* 3x3 matrix
*/
typedef struct mat3
{
	union
	{
		vec3 rows[3];
		float values[3][3];
		struct
		{
			float a, b, c;
			float d, e, f;
			float g, h, i;
		};
	};
} mat3;

/*
* Creates and identity matrix
*
* @returns A 3x3 matrix where the values in the main diagonal are 1s
*/
mat3 mat3_identity();

/*
* Multiplies two matrices together
*
* @param mat1, mat2 The operands of the multiplication
*
* @returns The product
*/
mat3 mat3_mul(mat3 mat1, mat3 mat2);

/*
* Transposes the matrix
*
* @param matrix The source matrix
*
* @returns The transposed matrix
*/
mat3 mat3_transpose(mat3 matrix);

/*
* Multiplies each value of the matrix with a scalar
*
* @param matrix The matrix to be scaled
* @param scale The scalar value to multiply with
*
* @returns The resulting matrix
*/
mat3 mat3_scale(mat3 matrix, float scale);

/*
* Inverts the matrix
*
* @param matrix The source matrix
*
* @returns The inverse matrix
*/
mat3 mat3_invert(mat3 matrix);

/*
* Determines if two matrices are equal
*
* @param a, b The matrices to be checked
*
* @returns A boolean indicating if they are equal
*/
bool mat3_eq(mat3 a, mat3 b);
