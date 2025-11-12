#pragma once

#include "vec4.h"

/*
* 4x4 matrix
*/
typedef struct mat4
{
	union
	{
		vec4 rows[4];
		float values[4][4];
		struct
		{
			float a, b, c, d;
			float e, f, g, h;
			float i, j, k, l;
			float m, n, o, p;
		};
	};
} mat4;

/*
* Creates and identity matrix
*
* @returns A 3x3 matrix where the values in the main diagonal are 1s
*/
mat4 mat4_identity();

/*
* Multiplies two matrices together
*
* @param mat1, mat2 The operands of the multiplication
*
* @returns The product
*/
mat4 mat4_mul(mat4 mat1, mat4 mat2);

/*
* Multiplies two matrices together to be used in rotation matrix
*
* @param mat1, mat2 The operands of the multiplication
*
* @returns The product where the resulting matrix's last row is the last row of the first operand
*/
mat4 mat4_mul_rot(mat4 mat1, mat4 mat2);

/*
* Transposes the matrix
*
* @param matrix The source matrix
*
* @returns The transposed matrix
*/
mat4 mat4_transpose(mat4 matrix);

/*
* Multiplies each value of the matrix with a scalar
*
* @param matrix The matrix to be scaled
* @param scale The scalar value to multiply with
*
* @returns The resulting matrix
*/
mat4 mat4_scale(mat4 matrix, float scale);

/*
* Inverts the matrix
*
* @param matrix The source matrix
*
* @returns The inverse matrix
*/
mat4 mat4_invert(mat4 matrix);

/*
* Determines if two matrices are equal
*
* @param a, b The matrices to be checked
*
* @returns A boolean indicating if they are equal
*/
bool mat4_eq(mat4 a, mat4 b);
