#pragma once

#include "defines.h"

typedef struct arena_allocator_t
{
	size_t size;
	void* allocation;
	void* pointer;
} arena_allocator_t;

bool arena_allocator_create(size_t max_size, arena_allocator_t* out_allocator);
void arena_allocator_destroy(arena_allocator_t* allocator);

void* arena_allocator_allocate(arena_allocator_t* allocator, size_t size);
