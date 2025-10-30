#pragma once

#include "vec3.h"
#include "mat4.h"

#define PI (3.141592654f)

float deg_to_rad(float deg);
float rad_to_deg(float rad);

mat4 mat4_translate(mat4 matrix, vec4 vector);

mat4 mat4_translate_x(mat4 matrix, float x);
mat4 mat4_translate_y(mat4 matrix, float y);
mat4 mat4_translate_z(mat4 matrix, float z);

mat4 mat4_rotate_x(mat4 matrix, float angle_rad);
mat4 mat4_rotate_y(mat4 matrix, float angle_rad);
mat4 mat4_rotate_z(mat4 matrix, float angle_rad);

mat4 mat4_scale_vec3(mat4 matrix, vec3 scalar);
mat4 mat4_scale_vec4(mat4 matrix, vec4 scalar);

mat4 mat4_perspective(float fov, float aspect_ratio, float near_plane, float far_plane);
mat4 mat4_look_at(vec3 eye, vec3 center, vec3 up);
