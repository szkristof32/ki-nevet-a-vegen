#include "sdl_renderer.h"

#include "infoc/core/engine.h"

#include "gl.h"
#include "texture.h"
#include "shader.h"
#include "vertex_array.h"

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string.h>

#undef bool

typedef struct sdl_renderer_t
{
	SDL_Renderer* renderer;
	SDL_Surface* surface;

	TTF_TextEngine* text_engine;
	TTF_Font* default_font;
	TTF_Font* big_font;

	vertex_array_t vertex_array;
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
	check_error(!vertex_array_create(&s_sdl_renderer->vertex_array), "Failed to create vertex array!");
	check_error(!texture_create_format(1280, 720, GL_RGBA8, &s_sdl_renderer->texture), "Failed to create OpenGL texture!");
	check_error(!shader_create("assets/shaders/sdl_shader.vert", "assets/shaders/sdl_shader.frag", &s_sdl_renderer->shader), "Failed to create SDL shader!");

	check_error(!TTF_Init(), "Failed to initialise SDL_ttf!");

	s_sdl_renderer->text_engine = TTF_CreateSurfaceTextEngine();
	check_error(!s_sdl_renderer->text_engine, "Failed to create SDL text engine!");

	s_sdl_renderer->default_font = TTF_OpenFont("assets/fonts/Roboto.ttf", 24.0f);
	check_error(!s_sdl_renderer->default_font, "Failed to open default font!\n%s", SDL_GetError());
	s_sdl_renderer->big_font = TTF_OpenFont("assets/fonts/Roboto.ttf", 40.0f);
	check_error(!s_sdl_renderer->big_font, "Failed to open big font!\n%s", SDL_GetError());

	return true;
}

void sdl_renderer_shutdown()
{
	shader_destroy(&s_sdl_renderer->shader);
	texture_destroy(&s_sdl_renderer->texture);
	vertex_array_destroy(&s_sdl_renderer->vertex_array);
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
	vertex_array_bind(&s_sdl_renderer->vertex_array);
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

SDL_Surface* sdl_renderer_get_surface()
{
	return s_sdl_renderer->surface;
}

void sdl_renderer_draw_text(const char* text, float x, float y, bool big_text)
{
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* text_surface = TTF_RenderText_Solid(!big_text ? s_sdl_renderer->default_font : s_sdl_renderer->big_font, text, 0, white);
	if (text_surface == NULL)
		return;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(s_sdl_renderer->renderer, text_surface);
	
	SDL_FRect src = { 0.0f, 0.0f, (float)text_surface->w, (float)text_surface->h };
	SDL_FRect dst = { x, y, (float)text_surface->w, (float)text_surface->h };
	SDL_RenderTexture(s_sdl_renderer->renderer, texture, &src, &dst);

	SDL_DestroyTexture(texture);
	SDL_DestroySurface(text_surface);
}

void sdl_renderer_get_text_size(const char* text, float* width, float* height, bool big_text)
{
	int32_t text_width, text_height;
	TTF_GetStringSize(!big_text ? s_sdl_renderer->default_font : s_sdl_renderer->big_font, text, 0, &text_width, &text_height);

	*width = (float)text_width;
	*height = (float)text_height;
}

void sdl_renderer_draw_square(float x, float y, float width, float height, vec4 colour)
{
	SDL_SetRenderDrawColorFloat(s_sdl_renderer->renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_FRect rect = { x, y, width, height };
	SDL_RenderFillRect(s_sdl_renderer->renderer, &rect);
}
