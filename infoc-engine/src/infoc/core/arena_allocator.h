#pragma once

#include "defines.h"

/**
 * Arena allocator
 */
typedef struct arena_allocator_t
{
	/** Holds the capacity of the arena allocator in bytes */
	size_t size;
	/** The pointer to the allocation */
	void* allocation;
	/** Pointer to the remaining block of the pool */
	void* pointer;
} arena_allocator_t;

/**
 * Creates an arena allocator.
 *
 * @param max_size The capacity of the allocator in bytes
 * @param out_allocator A pointer to an `arena_allocator_t` struct to be filled
 *
 * @returns A boolean indicating whether the operation finished successfully
 */
bool arena_allocator_create(size_t max_size, arena_allocator_t* out_allocator);
/**
 * Destroys the arena allocator.
 *
 * @param allocator A pointer to a valid `arena_allocator_t` struct
 */
void arena_allocator_destroy(arena_allocator_t* allocator);

/**
 * Allocates memory using the preallocated pool.
 *
 * @param allocator A pointer to a valid `arena_allocator_t` struct
 * @param size The desired memory block size in bytes
 *
 * @returns The memory block address if the pool had enough memory, otherwise `NULL`
 */
void* arena_allocator_allocate(arena_allocator_t* allocator, size_t size);
