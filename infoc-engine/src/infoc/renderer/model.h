#pragma once

#include "infoc/core/defines.h"

#include "mesh.h"
#include "texture.h"

/*
* Renderable model
*/
typedef struct model_t
{
	mesh_t mesh; /* Mesh */
	texture_t model_texture; /* Texture */
} model_t;

/*
* Frees model resources
*
* @param model The model
*/
void model_destroy(model_t* model);
