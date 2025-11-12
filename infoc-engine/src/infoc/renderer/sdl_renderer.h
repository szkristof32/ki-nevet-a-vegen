#pragma once

#include "infoc/core/defines.h"

#include "context.h"

#include <SDL3/SDL_render.h>

#undef bool

/*
* Initialises the SDL renderer
*
* @param context A pointer to a valid `context_t` struct
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool sdl_renderer_init(const context_t* context);
/*
* Shuts down the SDL renderer
*/
void sdl_renderer_shutdown();

/*
* Prepares the SDL renderer for frame rendering
*/
void sdl_renderer_begin_frame();
/*
* Renders the current frame with the SDL renderer
*/
void sdl_renderer_end_frame();

/*
* Window resize callback for the SDL renderer. Should only be called from window
*
* @param width The window width
* @param height The window height
*/
void sdl_renderer_on_window_resize(uint32_t width, uint32_t height);

/*
* Gets the native SDL_Renderer handle
*
* @returns The SDL_Renderer handle
*/
SDL_Renderer* sdl_renderer_get_handle();
SDL_Surface* sdl_renderer_get_surface();

/*
* Helper method to draw text to the screen
*
* @param text The text to be rendered
* @param x, y The coordinates of the text
*/
void sdl_renderer_draw_text(const char* text, float x, float y, bool big_text);
void sdl_renderer_get_text_size(const char* text, float* width, float* height, bool big_text);
