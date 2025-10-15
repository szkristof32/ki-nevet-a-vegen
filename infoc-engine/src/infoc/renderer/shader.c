#include "shader.h"

#include "gl.h"

#include "infoc/utils/file_utils.h"

#include <stdlib.h>
#include <string.h>

static uint32_t _shader_create_shader(const char* file_path, uint32_t stage);

bool shader_create(const char* vertex_path, const char* fragment_path, shader_t* out_shader)
{
	out_shader->program_handle = glCreateProgram();

	uint32_t vertex_shader = _shader_create_shader(vertex_path, GL_VERTEX_SHADER);
	uint32_t fragment_shader = _shader_create_shader(fragment_path, GL_FRAGMENT_SHADER);

	glAttachShader(out_shader->program_handle, vertex_shader);
	glAttachShader(out_shader->program_handle, fragment_shader);

	glLinkProgram(out_shader->program_handle);

	glDetachShader(out_shader->program_handle, vertex_shader);
	glDetachShader(out_shader->program_handle, fragment_shader);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return true;
}

void shader_destroy(shader_t* shader)
{
	glDeleteProgram(shader->program_handle);
	memset(shader, 0, sizeof(shader_t));
}

void shader_use(const shader_t* shader)
{
	glUseProgram(shader->program_handle);
}

uint32_t _shader_create_shader(const char* file_path, uint32_t stage)
{
	uint32_t shader = glCreateShader(stage);

	char* source = file_utils_read_file(file_path);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	free(source);

	return shader;
}
