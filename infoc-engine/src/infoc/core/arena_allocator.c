#include "arena_allocator.h"

#include <stdlib.h>
#include <string.h>

bool arena_allocator_create(size_t max_size, arena_allocator_t* out_allocator)
{
	check_error(max_size == 0, "Allocator max size must be greater than 0 bytes!");

#ifdef IC_DEBUGMALLOC
	debugmalloc_max_block_size((uint32_t)max_size);
#endif

	out_allocator->size = max_size;
	out_allocator->allocation = malloc(max_size);
	out_allocator->pointer = out_allocator->allocation;

	check_error(out_allocator->allocation == NULL, "Failed to allocate memory for arena!");

	memset(out_allocator->allocation, 0, max_size);

	return true;
}

void arena_allocator_destroy(arena_allocator_t* allocator)
{
	free(allocator->allocation);
	memset(allocator, 0, sizeof(arena_allocator_t));
}

void* arena_allocator_allocate(arena_allocator_t* allocator, size_t size)
{
	check_error((uint8_t*)allocator->pointer - (uint8_t*)allocator->allocation + size > allocator->size, "Not enough memory left in arena!");

	void* allocation = allocator->pointer;
	allocator->pointer = (uint8_t*)allocator->pointer + size;

	return allocation;
}
