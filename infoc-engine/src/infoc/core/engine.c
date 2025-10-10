#include "engine.h"

#include <string.h>

typedef struct engine_t
{
	arena_allocator_t allocator;
} engine_t;

static engine_t s_engine;

bool engine_initialise()
{
	bool success = arena_allocator_create(megabytes(10), &s_engine.allocator);
	if (!success)
	{
		fprintf(stderr, "Failed to create arena allocator!\n");
		return false;
	}

	return true;
}

void engine_shutdown()
{
	arena_allocator_destroy(&s_engine.allocator);
	memset(&s_engine, 0, sizeof(engine_t));
}

arena_allocator_t* engine_get_allocator()
{
	return &s_engine.allocator;
}
