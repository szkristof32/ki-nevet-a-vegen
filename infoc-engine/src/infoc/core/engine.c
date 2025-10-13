#include "engine.h"

#include "infoc/core/window.h"

#include "infoc/renderer/context.h"
#include "infoc/renderer/gl.h"

#include <string.h>

typedef struct engine_t
{
	arena_allocator_t allocator;
	window_t window;
	context_t context;

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

	success = context_create(&s_engine.window, &s_engine.context);
	if (!success)
	{
		fprintf(stderr, "Failed to create context!\n");
		return false;
	}

	s_engine.running = true;

	return true;
}

void engine_shutdown()
{
	context_destroy(&s_engine.context);
	window_destroy(&s_engine.window);
	arena_allocator_destroy(&s_engine.allocator);
	memset(&s_engine, 0, sizeof(engine_t));
}

void engine_run()
{
	while (s_engine.running)
	{
		window_update(&s_engine.window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		context_swap(&s_engine.context);

		s_engine.running = !window_should_close(&s_engine.window);
	}
}

arena_allocator_t* engine_get_allocator()
{
	return &s_engine.allocator;
}
