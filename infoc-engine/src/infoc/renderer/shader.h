#pragma once

#include "infoc/core/defines.h"

/**
 * Shader program
 */
typedef struct shader_t
{
	/** OpenGL program handle */
	uint32_t program_handle;
} shader_t;

/**
 * Creates an OpenGL graphics shader
 *
 * @param vertex_path The filepath of the vertex shader source
 * @param fragment_path The filepath of the fragment shader source
 * @param out_shader A pointer to a `shader_t` struct to be filled
 *
 * @returns A boolean indicating whether the operation finished succesfully
 */
bool shader_create(const char* vertex_path, const char* fragment_path, shader_t* out_shader);
/**
 * Destroys a graphics shader
 *
 * @param shader A pointer to a valid `shader_t` struct
 */
void shader_destroy(shader_t* shader);

/**
 * Binds a shader for use
 *
 * @param shader A pointer to a valid `shader_t` struct
 */
void shader_use(const shader_t* shader);
