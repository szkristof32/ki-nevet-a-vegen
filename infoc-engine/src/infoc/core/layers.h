#pragma once

#include "defines.h"

#include <SDL3/SDL_render.h>

#undef bool

typedef struct layer_t
{
	void (*on_attach)();
	void (*on_detach)();
	void (*on_update)(float timestep);
	void (*on_ui_render)(SDL_Renderer* renderer);
	void* internal_state;
} layer_t;

typedef struct layer_stack_t
{
	layer_t* layers; // darray
} layer_stack_t;

bool layer_stack_create(layer_stack_t* out_layer_stack);
void layer_stack_destroy(layer_stack_t* layer_stack);

void layer_stack_push_layer(layer_stack_t* layer_stack, layer_t* layer);
