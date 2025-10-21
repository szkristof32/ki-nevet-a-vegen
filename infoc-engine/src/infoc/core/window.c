#include "window.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include <SDL3/SDL.h>
#include <string.h>

#undef bool

typedef struct window_internal_t
{
	SDL_Window* window_handle;

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

	internal_state->window_handle = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!internal_state->window_handle)
	{
		fprintf(stderr, "Failed to create window!\n");
		return false;
	}

	return true;
}

void window_destroy(window_t* window)
{
	window_internal_t* internal_state = window->internal_state;
	SDL_DestroyWindow(internal_state->window_handle);

	SDL_Quit();
	memset(window, 0, sizeof(window_t));
}

static uint32_t _mouse_button_index(uint8_t button)
{
	switch (button)
	{
		case SDL_BUTTON_LEFT:	return 0;
		case SDL_BUTTON_RIGHT:	return 1;
		case SDL_BUTTON_MIDDLE:	return 2;
	}

	return -1;
}

void window_update(const window_t* window)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
			{
				window_internal_t* internal_state = window->internal_state;
				internal_state->should_close = true;
				break;
			}
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			case SDL_EVENT_MOUSE_BUTTON_UP:
			{
				SDL_MouseButtonEvent mouse_event = *(SDL_MouseButtonEvent*)&event;
				input_click_listener(_mouse_button_index(mouse_event.button), mouse_event.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
				break;
			}
			case SDL_EVENT_MOUSE_MOTION:
			{
				SDL_MouseMotionEvent mouse_event = *(SDL_MouseMotionEvent*)&event;
				float x = (float)mouse_event.x / (float)window->width;
				float y = (float)mouse_event.y / (float)window->height;
				input_move_listener(x, y);
				break;
			}
			case SDL_EVENT_MOUSE_WHEEL:
			{
				SDL_MouseWheelEvent mouse_event = *(SDL_MouseWheelEvent*)&event;
				input_scroll_listener((float)mouse_event.x, (float)mouse_event.y);
				break;
			}
		}
	}
}

bool window_should_close(const window_t* window)
{
	window_internal_t* internal_state = window->internal_state;
	return internal_state->should_close;
}

void* window_get_handle(const window_t* window)
{
	window_internal_t* internal_state = window->internal_state;
	return internal_state->window_handle;
}
