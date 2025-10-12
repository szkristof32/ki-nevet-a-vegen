#include "engine.h"

#include "infoc/core/window.h"

#include <string.h>

typedef struct engine_t
{
	arena_allocator_t allocator;
	window_t window;

	bool running;
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

	success = window_create(1280, 720, "Ki nevet a vegen?", &s_engine.window);
	if (!success)
	{
		fprintf(stderr, "Failed to create window!\n");
		return false;
	}

	s_engine.running = true;

	return true;
}

void engine_shutdown()
{
	window_destroy(&s_engine.window);
	arena_allocator_destroy(&s_engine.allocator);
	memset(&s_engine, 0, sizeof(engine_t));
}

void engine_run()
{
	while (s_engine.running)
	{
		window_update(&s_engine.window);

		s_engine.running = !window_should_close(&s_engine.window);
	}
}

arena_allocator_t* engine_get_allocator()
{
	return &s_engine.allocator;
}
