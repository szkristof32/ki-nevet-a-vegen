#include "shader.h"

#include "gl.h"

#include "infoc/utils/file_utils.h"

#include <stdlib.h>
#include <string.h>

static uint32_t _shader_create_shader(const char* file_path, uint32_t stage);

bool shader_create(const char* vertex_path, const char* fragment_path, shader_t* out_shader)
{
	memset(out_shader, 0, sizeof(shader_t));

	out_shader->program_handle = glCreateProgram();
	check_error(out_shader->program_handle == 0, "Failed to create shader program!");

	uint32_t vertex_shader = _shader_create_shader(vertex_path, GL_VERTEX_SHADER);
	uint32_t fragment_shader = _shader_create_shader(fragment_path, GL_FRAGMENT_SHADER);
	check_error(vertex_shader == 0 || fragment_shader == 0, "Failed to create either of the shader stages!");

	glAttachShader(out_shader->program_handle, vertex_shader);
	glAttachShader(out_shader->program_handle, fragment_shader);

	glLinkProgram(out_shader->program_handle);

	int32_t status;
	glGetProgramiv(out_shader->program_handle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		char buffer[512];
		glGetProgramInfoLog(out_shader->program_handle, 512, NULL, buffer);
		log_error(buffer);
	}

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
	glShaderSource(shader, 1, (const char**)&source, NULL);
	glCompileShader(shader);
	free(source);

	return shader;
}
