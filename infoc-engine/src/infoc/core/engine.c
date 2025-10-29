#include "engine.h"

#include "infoc/core/window.h"
#include "infoc/core/layers.h"
#include "infoc/core/darray.h"
#include "infoc/core/input.h"

#include "infoc/renderer/context.h"
#include "infoc/renderer/gl.h"
#include "infoc/renderer/texture.h"
#include "infoc/renderer/static_renderer.h"
#include "infoc/renderer/sdl_renderer.h"

#include <string.h>

typedef struct engine_t
{
	arena_allocator_t allocator;
	window_t window;
	context_t context;

	layer_stack_t layer_stack;
	texture_t default_texture;

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

	success = window_create(1280, 720, u8"Ne nevessch korán!", &s_engine.window);
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

	success = texture_create_empty(1, 1, &s_engine.default_texture);
	if (!success)
	{
		fprintf(stderr, "Failed to create default texture!\n");
		return false;
	}
	uint32_t default_texture_data = 0xffffffff;
	texture_set_data(&s_engine.default_texture, &default_texture_data);

	success = input_initialise();
	if (!success)
	{
		fprintf(stderr, "Failed to initialise input!\n");
		return false;
	}

	success = layer_stack_create(&s_engine.layer_stack);
	if (!success)
	{
		fprintf(stderr, "Failed to create layer stack!\n");
		return false;
	}

	success = static_renderer_init();
	if (!success)
	{
		fprintf(stderr, "Failed to initialise static renderer!\n");
		return false;
	}

	success = sdl_renderer_init(&s_engine.context);
	if (!success)
	{
		fprintf(stderr, "Failed to initialise SDL renderer!\n");
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

	sdl_renderer_shutdown();
	static_renderer_shutdown();
	layer_stack_destroy(&s_engine.layer_stack);
	input_shutdown();
	context_destroy(&s_engine.context);
	window_destroy(&s_engine.window);
	arena_allocator_destroy(&s_engine.allocator);
	memset(&s_engine, 0, sizeof(engine_t));
}

void engine_run()
{
	while (s_engine.running)
	{
		float delta = 0.0f;

		input_update();
		window_update(&s_engine.window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static_renderer_begin_frame();

		for (size_t i = 0; i < darray_count(s_engine.layer_stack.layers); i++)
		{
			layer_t* layer = &s_engine.layer_stack.layers[i];
			if (layer->on_update)
				layer->on_update(delta);
		}

		static_renderer_end_frame();

		sdl_renderer_begin_frame();
		for (size_t i = 0; i < darray_count(s_engine.layer_stack.layers); i++)
		{
			layer_t* layer = &s_engine.layer_stack.layers[i];
			if (layer->on_ui_render)
				layer->on_ui_render(sdl_renderer_get_handle());
		}
		sdl_renderer_end_frame();

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

struct texture_t* engine_get_default_texture()
{
	return &s_engine.default_texture;
}
