#pragma once

#include "game_object.h"
#include "camera.h"

/**
 * Scene
 */
typedef struct scene_t
{
	/** Scene camera */
	camera_t camera;
	/** Dynamic array of game objects */
	game_object_t* game_objects;
} scene_t;

/**
 * Creates a scene
 *
 * @param out_scene A pointer to a `scene_t` struct to be filled
 */
void scene_create(scene_t* out_scene);
/**
 * Destroys a scene
 *
 * @param scene A pointer to a valid `scene_t` struct
 */
void scene_destroy(scene_t* scene);

/**
 * Inserts and initialises a new object into the scene
 *
 * @param scene The scene which the object should be created in
 *
 * @returns The index of the game object in the object array
 */
game_object_index_t scene_new_object(scene_t* scene);
/**
 * Finds the game object associated with the given index
 *
 * @param scene The scene which contains the object
 * @param index The index of the game object (returned by `scene_new_object`)
 *
 * @returns The game object at the given index if exists, otherwise NULL
 */
game_object_t* scene_get_object(scene_t* scene, game_object_index_t index);
