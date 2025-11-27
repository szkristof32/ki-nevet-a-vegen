#pragma once

#include "vec3.h"
#include "mat4.h"

#define PI (3.141592654f)

/**
 * Converts degrees to radians
 *
 * @param deg Angle in degrees
 *
 * @returns Angle in radians
 */
float deg_to_rad(float deg);
/**
 * Converts radians to degrees
 *
 * @param deg Angle in radians
 *
 * @returns Angle in degrees
 */
float rad_to_deg(float rad);

/**
 * Creates a 4x4 translation matrix
 *
 * @param matrix Source matrix
 * @param vector Translation
 *
 * @returns The translation matrix
 */
mat4 mat4_translate(mat4 matrix, vec4 vector);

/**
 * Creates a 4x4 translation matrix
 *
 * @param matrix Source matrix
 * @param x Translation along the x axis
 *
 * @returns The translation matrix
 */
mat4 mat4_translate_x(mat4 matrix, float x);
/**
 * Creates a 4x4 translation matrix
 *
 * @param matrix Source matrix
 * @param y Translation along the y axis
 *
 * @returns The translation matrix
 */
mat4 mat4_translate_y(mat4 matrix, float y);
/**
 * Creates a 4x4 translation matrix
 *
 * @param matrix Source matrix
 * @param z Translation along the z axis
 *
 * @returns The translation matrix
 */
mat4 mat4_translate_z(mat4 matrix, float z);

/**
 * Creates a 4x4 rotation matrix
 *
 * @param matrix Source matrix
 * @param x Rotation in radians along the x axis
 *
 * @returns The rotation matrix
 */
mat4 mat4_rotate_x(mat4 matrix, float angle_rad);
/**
 * Creates a 4x4 rotation matrix
 *
 * @param matrix Source matrix
 * @param y Rotation in radians along the y axis
 *
 * @returns The rotation matrix
 */
mat4 mat4_rotate_y(mat4 matrix, float angle_rad);
/**
 * Creates a 4x4 rotation matrix
 *
 * @param matrix Source matrix
 * @param z Rotation in radians along the z axis
 *
 * @returns The rotation matrix
 */
mat4 mat4_rotate_z(mat4 matrix, float angle_rad);

/**
 * Creates a 4x4 scale matrix
 *
 * @param matrix Source matrix
 * @param scalar Scalar
 *
 * @returns The scale matrix
 */
mat4 mat4_scale_vec3(mat4 matrix, vec3 scalar);
/**
 * Creates a 4x4 scale matrix
 *
 * @param matrix Source matrix
 * @param scalar Scalar
 *
 * @returns The scale matrix
 */
mat4 mat4_scale_vec4(mat4 matrix, vec4 scalar);

/**
 * Creates a 4x4 perspective projection matrix
 *
 * @param fov Field of view in radians
 * @param aspect_ratio The aspect ratio of the image
 * @param near_plane The distance of the near clipping plane
 * @param far_plane The distance of the far clipping plane
 *
 * @returns The projection matrix
 */
mat4 mat4_perspective(float fov, float aspect_ratio, float near_plane, float far_plane);
/**
 * Creates a 4x4 view matrix where the camera always faces a center point
 *
 * @param eye The position of the camera
 * @param center The center point to be faced
 * @param up The unit vector along the up axis
 *
 * @returns The view matrix
 */
mat4 mat4_look_at(vec3 eye, vec3 center, vec3 up);
