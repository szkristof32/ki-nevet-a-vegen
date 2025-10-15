#pragma once

#include "infoc/core/defines.h"

typedef struct shader_t
{
	uint32_t program_handle;
} shader_t;

bool shader_create(const char* vertex_path, const char* fragment_path, shader_t* out_shader);
void shader_destroy(shader_t* shader);

void shader_use(const shader_t* shader);
