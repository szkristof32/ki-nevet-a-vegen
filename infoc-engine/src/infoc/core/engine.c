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

#include <SDL3/SDL.h>
#include <string.h>

typedef struct engine_t
{
	arena_allocator_t allocator;
	window_t window;
	context_t context;

	layer_stack_t layer_stack;
	texture_t default_texture;

	bool running;
	bool close_request;
} engine_t;

static engine_t s_engine;

bool engine_initialise()
{
	bool success = arena_allocator_create(megabytes(10), &s_engine.allocator);
	check_error(!success, "Failed to create arena allocator!");

	success = window_create(1280, 720, u8"Ludo", &s_engine.window);
	check_error(!success, "Failed to create window!");

	success = context_create(&s_engine.window, &s_engine.context);
	check_error(!success, "Failed to create context!");

	success = texture_create_empty(1, 1, &s_engine.default_texture);
	check_error(!success, "Failed to create default texture!");
	uint32_t default_texture_data = 0xffffffff;
	texture_set_data(&s_engine.default_texture, &default_texture_data);

	success = input_initialise();
	check_error(!success, "Failed to initialise input!");

	success = layer_stack_create(&s_engine.layer_stack);
	check_error(!success, "Failed to create layer stack!");

	success = static_renderer_init();
	check_error(!success, "Failed to initialise static renderer!");

	success = sdl_renderer_init(&s_engine.context);
	check_error(!success, "Failed to initialise SDL renderer!");

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
	engine_on_window_resize(s_engine.window.width, s_engine.window.height);

	uint64_t last_frame_time = SDL_GetTicks();

	while (s_engine.running)
	{
		uint64_t current_time = SDL_GetTicks();
		float delta = (float)(current_time - last_frame_time) / 1000.0f;
		last_frame_time = current_time;

		input_update();
		window_update(&s_engine.window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, s_engine.window.width, s_engine.window.height);

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

		s_engine.running = !window_should_close(&s_engine.window) && !s_engine.close_request;
	}
}

void engine_attach_layer(layer_t* layer)
{
	layer_stack_push_layer(&s_engine.layer_stack, layer);

	if (layer->on_attach)
		layer->on_attach();
}

void engine_detach_layer(layer_t* layer)
{
	layer_stack_pop_layer(&s_engine.layer_stack, layer);

	if (layer->on_detach)
		layer->on_detach();
}

void engine_on_window_resize(uint32_t width, uint32_t height)
{
	static_renderer_on_window_resize(width, height);
	sdl_renderer_on_window_resize(width, height);

	for (size_t i = 0; i < darray_count(s_engine.layer_stack.layers); i++)
	{
		layer_t* layer = &s_engine.layer_stack.layers[i];
		if (layer->on_window_resize)
			layer->on_window_resize(width, height);
	}
}

void engine_request_close()
{
	s_engine.close_request = true;
}

arena_allocator_t* engine_get_allocator()
{
	return &s_engine.allocator;
}

struct texture_t* engine_get_default_texture()
{
	return &s_engine.default_texture;
}
