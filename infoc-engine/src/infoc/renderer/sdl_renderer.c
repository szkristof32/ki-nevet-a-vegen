#include "sdl_renderer.h"

#include "infoc/core/engine.h"

#include "gl.h"
#include "texture.h"
#include "shader.h"

#include <SDL3/SDL_render.h>

#include <string.h>

#undef bool

typedef struct sdl_renderer_t
{
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	texture_t texture;
	shader_t shader;
} sdl_renderer_t;

sdl_renderer_t* s_sdl_renderer = NULL;

bool sdl_renderer_init(const context_t* context)
{
	arena_allocator_t* allocator = engine_get_allocator();
	s_sdl_renderer = arena_allocator_allocate(allocator, sizeof(sdl_renderer_t));

	s_sdl_renderer->surface = SDL_CreateSurface(1280, 720, SDL_PIXELFORMAT_RGBA32);
	check_error(!s_sdl_renderer->surface, "Failed to create SDL surface!");

	s_sdl_renderer->renderer = SDL_CreateSoftwareRenderer(s_sdl_renderer->surface);
	check_error(!s_sdl_renderer->renderer, "Failed to create SDL renderer!");
	check_error(!texture_create_format(1280, 720, GL_RGBA8, &s_sdl_renderer->texture), "Failed to create OpenGL texture!");
	check_error(!shader_create("assets/shaders/sdl_shader.vert", "assets/shaders/sdl_shader.frag", &s_sdl_renderer->shader), "Failed to create SDL shader!");

	return true;
}

void sdl_renderer_shutdown()
{
	shader_destroy(&s_sdl_renderer->shader);
	texture_destroy(&s_sdl_renderer->texture);
	SDL_DestroyRenderer(s_sdl_renderer->renderer);
	SDL_DestroySurface(s_sdl_renderer->surface);

	s_sdl_renderer = NULL;
}

void sdl_renderer_begin_frame()
{
	SDL_SetRenderDrawColorFloat(s_sdl_renderer->renderer, 0.0f, 0.0f, 0.0f, 0.0f);
	SDL_RenderClear(s_sdl_renderer->renderer);
}

void sdl_renderer_end_frame()
{
	SDL_RenderPresent(s_sdl_renderer->renderer);
	SDL_FlipSurface(s_sdl_renderer->surface, SDL_FLIP_VERTICAL);
	texture_set_data_format(&s_sdl_renderer->texture, s_sdl_renderer->surface->pixels, GL_RGBA);

	glDisable(GL_DEPTH_TEST);
	texture_bind(&s_sdl_renderer->texture, 0);
	shader_use(&s_sdl_renderer->shader);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glEnable(GL_DEPTH_TEST);
}

void sdl_renderer_on_window_resize(uint32_t width, uint32_t height)
{
	SDL_DestroyRenderer(s_sdl_renderer->renderer);
	SDL_DestroySurface(s_sdl_renderer->surface);

	s_sdl_renderer->surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
	s_sdl_renderer->renderer = SDL_CreateSoftwareRenderer(s_sdl_renderer->surface);

	texture_destroy(&s_sdl_renderer->texture);
	texture_create_format(width, height, GL_RGBA8, &s_sdl_renderer->texture);
}

SDL_Renderer* sdl_renderer_get_handle()
{
	return s_sdl_renderer->renderer;
}
