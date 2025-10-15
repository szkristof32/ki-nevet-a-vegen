#include "engine.h"

#include "infoc/core/window.h"
#include "infoc/core/layers.h"
#include "infoc/core/darray.h"

#include "infoc/renderer/context.h"
#include "infoc/renderer/gl.h"

// TODO: temporary
#include "infoc/renderer/buffers.h"
#include "infoc/renderer/vertex_array.h"

#include <string.h>

typedef struct engine_t
{
	arena_allocator_t allocator;
	window_t window;
	context_t context;

	layer_stack_t layer_stack;

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

	success = layer_stack_create(&s_engine.layer_stack);
	if (!success)
	{
		fprintf(stderr, "Failed to create layer stack!\n");
		return false;
	}

	s_engine.running = true;

	return true;
}

void engine_shutdown()
{
	for (size_t i = 0; i < darray_count(s_engine.layer_stack.layers); i++)
	{
		layer_t* layer = &s_engine.layer_stack.layers[i];
		if (layer->on_detach)
			layer->on_detach();
	}

	context_destroy(&s_engine.context);
	window_destroy(&s_engine.window);
	arena_allocator_destroy(&s_engine.allocator);
	memset(&s_engine, 0, sizeof(engine_t));
}

void engine_run()
{
	float data[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	vertex_buffer_t vertex_buffer;
	vertex_buffer_create(data, sizeof(data), &vertex_buffer);

	vertex_array_t vertex_array;
	vertex_array_create(&vertex_array);

	vertex_array_bind(&vertex_array);
	vertex_buffer_bind(&vertex_buffer);

	vertex_array_add_attribute(&vertex_array, vertex_attribute_type_float3);
	vertex_array_bake_layout(&vertex_array);

	while (s_engine.running)
	{
		float delta = 0.0f;

		window_update(&s_engine.window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (size_t i = 0; i < darray_count(s_engine.layer_stack.layers); i++)
		{
			layer_t* layer = &s_engine.layer_stack.layers[i];
			if (layer->on_update)
				layer->on_update(delta);
		}

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		context_swap(&s_engine.context);

		s_engine.running = !window_should_close(&s_engine.window);
	}
}

void engine_attach_layer(layer_t* layer)
{
	layer_stack_push_layer(&s_engine.layer_stack, layer);

	if (layer->on_attach)
		layer->on_attach();
}

arena_allocator_t* engine_get_allocator()
{
	return &s_engine.allocator;
}
