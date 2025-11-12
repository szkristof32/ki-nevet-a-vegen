#pragma once

#include "defines.h"

#include <SDL3/SDL_render.h>

#undef bool

/*
* Layer
*/
typedef struct layer_t
{
	void (*on_attach)(); /* Attach callback. Called when layer is pushed onto a layer stack */
	void (*on_detach)(); /* Detach callback. Called when layer is popped from a layer stack */
	void (*on_update)(float timestep); /* Update callback. Called when the game loop processes the layer */
	void (*on_ui_render)(SDL_Renderer* renderer); /* UI render callback. Called when the game UI is rendererd */
	void (*on_window_resize)(uint32_t width, uint32_t height); /* Window resize callback */
	void* internal_state; /* Pointer to a block of memory owned by each layer */
} layer_t;

/*
* Layer stack
*/
typedef struct layer_stack_t
{
	layer_t* layers; /* A dynamic array of layers */
} layer_stack_t;

/*
* Creates a layer stack
*
* @param out_layer_stack A pointer to a `layer_stack_t` struct to be filled
*
* @returns A boolean inidicating whether the operation finished succesfully
*/
bool layer_stack_create(layer_stack_t* out_layer_stack);
/*
* Destroys a layer stack
*
* @param layer_stack A pointer to a valid `layer_stack_t` struct
*/
void layer_stack_destroy(layer_stack_t* layer_stack);

/*
* Pushes a layer to the top of the stack
*
* @param layer_stack A pointer to a `layer_stack_t` struct to be pushed to
* @param layer A pointer to a `layer_t` struct to be pushed to the stack
*/
void layer_stack_push_layer(layer_stack_t* layer_stack, layer_t* layer);
void layer_stack_pop_layer(layer_stack_t* layer_stack, layer_t* layer);
