#pragma once

#include "infoc/core/defines.h"

#include "mesh.h"
#include "texture.h"

typedef struct model_t
{
	mesh_t mesh;
	texture_t model_texture;
} model_t;
