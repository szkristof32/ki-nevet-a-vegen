#include "window.h"

#include "infoc/core/engine.h"

#include <SDL3/SDL.h>
#include <string.h>

#undef bool

typedef struct window_internal_t
{
	SDL_Window* window_handle;
	SDL_Renderer* renderer_handle;

	bool should_close;
} window_internal_t;

bool window_create(uint32_t width, uint32_t height, const char* title, window_t* out_window)
{
	memset(out_window, 0, sizeof(window_t));
	if (width == 0 || height == 0)
	{
		fprintf(stderr, "Window width/height mustn't be 0!\n");
		return false;
	}
	out_window->width = width;
	out_window->height = height;

	arena_allocator_t* allocator = engine_get_allocator();
	window_internal_t* internal_state = arena_allocator_allocate(allocator, sizeof(window_internal_t));
	if (internal_state == NULL)
	{
		fprintf(stderr, "Failed to allocate window internal state!\n");
		return false;
	}

	out_window->internal_state = internal_state;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Failed to initialise SDL (%s)!\n", SDL_GetError());
		return false;
	}

	if (!SDL_CreateWindowAndRenderer(title, width, height, SDL_WINDOW_RESIZABLE, &internal_state->window_handle, &internal_state->renderer_handle))
	{
		fprintf(stderr, "Failed to create window!\n");
		return false;
	}

	if (!SDL_SetRenderLogicalPresentation(internal_state->renderer_handle, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX))
	{
		fprintf(stderr, "Failed to initialise renderer!\n");
		return false;
	}

	return true;
}

void window_destroy(window_t* window)
{
	SDL_Quit();
	memset(window, 0, sizeof(window_t));
}

void window_update(const window_t* window)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			window_internal_t* internal_state = window->internal_state;
			internal_state->should_close = true;
		}
	}
}

bool window_should_close(const window_t* window)
{
	window_internal_t* internal_state = window->internal_state;
	return internal_state->should_close;
}
