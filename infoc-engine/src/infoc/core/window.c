#include "window.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include <SDL.h>
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
	check_error(width == 0 || height == 0, "Window width/height mustn't be 0!");
	out_window->width = width;
	out_window->height = height;

	arena_allocator_t* allocator = engine_get_allocator();
	window_internal_t* internal_state = arena_allocator_allocate(allocator, sizeof(window_internal_t));
	check_error(internal_state == NULL, "Failed to allocate window internal state!");

	out_window->internal_state = internal_state;

	check_error(SDL_Init(SDL_INIT_VIDEO), "Failed to initialise SDL (%s)!", SDL_GetError());

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	internal_state->window_handle = SDL_CreateWindow(title, 
		(display_mode.w - width) / 2, (display_mode.h - height) / 2, width, height, 
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	check_error(!internal_state->window_handle, "Failed to create window!");

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

void window_update(window_t* window)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				window_internal_t* internal_state = window->internal_state;
				internal_state->should_close = true;
				break;
			}
			case SDL_WINDOWEVENT:
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					window->width = event.window.data1;
					window->height = event.window.data2;
					engine_on_window_resize(window->width, window->height);
				}
			}
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			{
				SDL_MouseButtonEvent mouse_event = *(SDL_MouseButtonEvent*)&event;
				input_click_listener(_mouse_button_index(mouse_event.button), mouse_event.type == SDL_MOUSEBUTTONDOWN);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				SDL_MouseMotionEvent mouse_event = *(SDL_MouseMotionEvent*)&event;
				float x = (float)mouse_event.x / (float)window->width;
				float y = (float)mouse_event.y / (float)window->height;
				input_move_listener(x, y);
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				SDL_MouseWheelEvent mouse_event = *(SDL_MouseWheelEvent*)&event;
				input_scroll_listener((float)mouse_event.x, (float)mouse_event.y);
				break;
			}
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				SDL_KeyboardEvent keyboard_event = *(SDL_KeyboardEvent*)&event;
				input_key_listener(keyboard_event.keysym.sym, keyboard_event.type == SDL_KEYDOWN);
				break;
			}
			case SDL_TEXTINPUT:
			{
				SDL_TextInputEvent text_input_event = *(SDL_TextInputEvent*)&event;
				input_type_listener(text_input_event.text[0]);
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

void window_start_text_input(const window_t* window)
{
	SDL_StartTextInput();
}

void window_stop_text_input(const window_t* window)
{
	SDL_StopTextInput();
}
