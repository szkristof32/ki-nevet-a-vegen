#pragma once

#include "infoc/core/defines.h"

#include "context.h"

#include <SDL3/SDL_render.h>

#undef bool

bool sdl_renderer_init(const context_t* context);
void sdl_renderer_shutdown();

void sdl_renderer_begin_frame();
void sdl_renderer_end_frame();

SDL_Renderer* sdl_renderer_get_handle();
