#include "input.h"

#include "engine.h"

#include <string.h>

typedef struct mouse_t
{
	bool buttons_down[3];
	bool buttons_clicked[3];
	bool buttons_released[3];

	float x, y;
	float dx, dy;
	float scroll;
	float last_x, last_y;
} mouse_t;

typedef struct input_t
{
	mouse_t mouse;
} input_t;

static input_t* s_input = NULL;

bool input_initialise()
{
	arena_allocator_t* allocator = engine_get_allocator();

	s_input = arena_allocator_allocate(allocator, sizeof(input_t));
	if (s_input == NULL)
	{
		fprintf(stderr, "Failed to initialise input!\n");
		return false;
	}

	return true;
}

void input_shutdown()
{
	s_input = NULL;
}

void input_update()
{
	memset(s_input->mouse.buttons_clicked, 0, sizeof(s_input->mouse.buttons_clicked));
	memset(s_input->mouse.buttons_released, 0, sizeof(s_input->mouse.buttons_released));

	s_input->mouse.dx = s_input->mouse.x - s_input->mouse.last_x;
	s_input->mouse.dy = s_input->mouse.y - s_input->mouse.last_y;
	s_input->mouse.last_x = s_input->mouse.x;
	s_input->mouse.last_y = s_input->mouse.y;
	s_input->mouse.scroll = 0.0f;
}

void input_move_listener(float x, float y)
{
	s_input->mouse.x = x;
	s_input->mouse.y = y;
}

void input_click_listener(int button, bool pressed)
{
	s_input->mouse.buttons_down[button] = pressed;
	
	if (pressed)
		s_input->mouse.buttons_clicked[button] = true;
	else
		s_input->mouse.buttons_released[button] = true;
}

void input_scroll_listener(float scroll_x, float scroll_y)
{
	s_input->mouse.scroll = scroll_y;
}

bool input_is_mouse_button_down(uint32_t button)
{
	return button < 3 && s_input->mouse.buttons_down[button];
}

bool input_is_mouse_button_clicked(uint32_t button)
{
	return button < 3 && s_input->mouse.buttons_clicked[button];
}

bool input_is_mouse_button_released(uint32_t button)
{
	return button < 3 && s_input->mouse.buttons_released[button];
}

float input_get_mouse_x()
{
	return s_input->mouse.x;
}

float input_get_mouse_y()
{
	return s_input->mouse.y;
}

float input_get_mouse_dx()
{
	return s_input->mouse.dx;
}

float input_get_mouse_dy()
{
	return s_input->mouse.dy;
}

float input_get_mouse_scroll()
{
	return s_input->mouse.scroll;
}
