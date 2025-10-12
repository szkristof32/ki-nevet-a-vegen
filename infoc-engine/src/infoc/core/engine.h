#pragma once

#include "defines.h"
#include "arena_allocator.h"

bool engine_initialise();
void engine_shutdown();

void engine_run();

arena_allocator_t* engine_get_allocator();
