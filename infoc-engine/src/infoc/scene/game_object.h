#pragma once

#include "infoc/core/defines.h"
#include "infoc/renderer/model.h"

#include "infoc/math/vec3.h"
#include "infoc/math/mat4.h"

typedef struct transform_t
{
	vec3 position;
	vec3 rotation;
	vec3 scale;
} transform_t;

typedef struct game_object_t
{
	transform_t transform;
	model_t model;
	vec4 colour;
	uint32_t index;
} game_object_t;

mat4 transform_get_model_matrix(transform_t* transform);

void game_object_destroy(game_object_t* object);
