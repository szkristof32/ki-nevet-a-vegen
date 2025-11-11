#pragma once

#include "infoc/core/defines.h"
#include "infoc/renderer/model.h"

#include "infoc/math/vec3.h"
#include "infoc/math/mat4.h"

/*
* Affine transformations
*/
typedef struct transform_t
{
	vec3 position; /* Translation */
	vec3 rotation; /* Rotation */
	vec3 scale; /* Scale */
} transform_t;

/*
* Game object
*/
typedef struct game_object_t
{
	transform_t transform; /* Object transformation */
	model_t model; /* Object model */
	vec4 colour; /* Object colour */
	uint32_t index; /* Object index (used for mouse picking) */
} game_object_t;

/*
* Game object index into objects list
* It is neccesary since the scene's object dynamic array data section can change location,
* thus the pointers can point to wrong locations
*/
typedef uint32_t game_object_index_t;

/*
* Calculates the transformation matrix of an affine transformation
*
* @param transform A pointer to a `transform_t` struct
*
* @returns The transformation matrix
*/
mat4 transform_get_model_matrix(transform_t* transform);

/*
* Destroys a game object
*
* @param object A pointer to a valid `game_object_t` struct
*/
void game_object_destroy(game_object_t* object);
