#pragma once

#include "defines.h"

typedef struct window_t
{
	uint32_t width;
	uint32_t height;

	void* internal_state;
} window_t;

bool window_create(uint32_t width, uint32_t height, const char* title, window_t* out_window);
void window_destroy(window_t* window);

void window_update(const window_t* window);
bool window_should_close(const window_t* window);

void* window_get_handle(const window_t* window);
