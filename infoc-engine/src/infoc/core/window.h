#pragma once

#include "defines.h"

/*
* Window
*/
typedef struct window_t
{
	uint32_t width; /* Window width */
	uint32_t height; /* Window height */

	void* internal_state; /* Internal window state not exposed */
} window_t;

/*
* Creates a window
*
* @param width The width of the window
* @param height The height of the window
* @param title The title of the window
* @param out_window A pointer to a `window_t` struct to be filled
*
* @returns A boolean inidicating whether the operation finished succesfully
*/
bool window_create(uint32_t width, uint32_t height, const char* title, window_t* out_window);
/*
* Destroys a window
*
* @param window A pointer to a valid `window_t` struct
*/
void window_destroy(window_t* window);

/*
* Updates the window, calls the event callbacks
*
* @param window A pointer to a valid `window_t` struct
*/
void window_update(window_t* window);
/*
* Checks if the window has been signaled to close
*
* @param window A pointer to a valid `window_t` struct
*
* @returns A boolean indicating if the window should close
*/
bool window_should_close(const window_t* window);

/*
* Gets the internal handle of the window
*
* @param window A pointer to a valid `window_t` struct
*
* @returns The SDL handle of the window cast to `void*`
*/
void* window_get_handle(const window_t* window);
