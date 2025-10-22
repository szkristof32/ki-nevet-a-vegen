#pragma once

#include "defines.h"
#include "arena_allocator.h"
#include "layers.h"

bool engine_initialise();
void engine_shutdown();

void engine_run();

void engine_attach_layer(layer_t* layer);

arena_allocator_t* engine_get_allocator();
struct texture_t* engine_get_default_texture();
