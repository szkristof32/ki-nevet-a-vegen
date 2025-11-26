#include "sdl_renderer.h"

#include "infoc/core/engine.h"

#include "gl.h"
#include "texture.h"
#include "shader.h"
#include "vertex_array.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <string.h>

#undef bool

typedef struct sdl_renderer_t
{
	SDL_Renderer* renderer;
	SDL_Surface* surface;

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

	s_sdl_renderer->surface = SDL_CreateRGBSurfaceWithFormat(0, 1280, 720, 8, SDL_PIXELFORMAT_RGBA32);
	check_error(!s_sdl_renderer->surface, "Failed to create SDL surface!");

	s_sdl_renderer->renderer = SDL_CreateSoftwareRenderer(s_sdl_renderer->surface);
	check_error(!s_sdl_renderer->renderer, "Failed to create SDL renderer!");
	check_error(!vertex_array_create(&s_sdl_renderer->vertex_array), "Failed to create vertex array!");
	check_error(!texture_create_format(1280, 720, GL_RGBA8, &s_sdl_renderer->texture), "Failed to create OpenGL texture!");
	check_error(!shader_create("assets/shaders/sdl_shader.vert", "assets/shaders/sdl_shader.frag", &s_sdl_renderer->shader), "Failed to create SDL shader!");

	check_error(TTF_Init(), "Failed to initialise SDL_ttf!");
	check_error(!IMG_Init(IMG_INIT_PNG), "Failed to initialise SDL_image!");

	s_sdl_renderer->default_font = TTF_OpenFont("assets/fonts/Roboto.ttf", 24);
	check_error(!s_sdl_renderer->default_font, "Failed to open default font!\n%s", SDL_GetError());
	s_sdl_renderer->big_font = TTF_OpenFont("assets/fonts/Roboto.ttf", 40);
	check_error(!s_sdl_renderer->big_font, "Failed to open big font!\n%s", SDL_GetError());

	return true;
}

void sdl_renderer_shutdown()
{
	shader_destroy(&s_sdl_renderer->shader);
	texture_destroy(&s_sdl_renderer->texture);
	vertex_array_destroy(&s_sdl_renderer->vertex_array);
	SDL_DestroyRenderer(s_sdl_renderer->renderer);
	SDL_FreeSurface(s_sdl_renderer->surface);

	s_sdl_renderer = NULL;
}

void sdl_renderer_begin_frame()
{
	SDL_SetRenderDrawColor(s_sdl_renderer->renderer, 0, 0, 0, 0);
	SDL_RenderClear(s_sdl_renderer->renderer);
}

void sdl_renderer_end_frame()
{
	SDL_RenderPresent(s_sdl_renderer->renderer);
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
	SDL_FreeSurface(s_sdl_renderer->surface);

	s_sdl_renderer->surface = SDL_CreateRGBSurfaceWithFormat(0, 1280, 720, 8, SDL_PIXELFORMAT_RGBA32);
	s_sdl_renderer->renderer = SDL_CreateSoftwareRenderer(s_sdl_renderer->surface);

	texture_destroy(&s_sdl_renderer->texture);
	texture_create_format(width, height, GL_RGBA8, &s_sdl_renderer->texture);
}

SDL_Surface* sdl_renderer_get_surface()
{
	return s_sdl_renderer->surface;
}

void sdl_renderer_draw_text(const char* text, uint32_t x, uint32_t y, bool big_text)
{
	SDL_Color white = { 255, 255, 255 };
	SDL_Surface* text_surface = TTF_RenderText_Solid(!big_text ? s_sdl_renderer->default_font : s_sdl_renderer->big_font, text, white);
	if (text_surface == NULL)
		return;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(s_sdl_renderer->renderer, text_surface);

	SDL_Rect src = { 0, 0, text_surface->w, text_surface->h };
	SDL_Rect dst = { x, y, text_surface->w, text_surface->h };
	SDL_RenderCopy(s_sdl_renderer->renderer, texture, &src, &dst);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text_surface);
}

void sdl_renderer_get_text_size(const char* text, uint32_t* width, uint32_t* height, bool big_text)
{
	int32_t text_width, text_height;
	TTF_SizeUTF8(!big_text ? s_sdl_renderer->default_font : s_sdl_renderer->big_font, text, &text_width, &text_height);

	*width = (uint32_t)text_width;
	*height = (uint32_t)text_height;
}

void sdl_renderer_draw_square(uint32_t x, uint32_t y, uint32_t width, uint32_t height, vec4 colour)
{
	colour = vec4_max(colour, vec4_scalar(0.0f));
	SDL_Rect rect = { x, y, width, height };
	SDL_SetRenderDrawColor(s_sdl_renderer->renderer,
		(uint8_t)(colour.r * 0xff),
		(uint8_t)(colour.g * 0xff),
		(uint8_t)(colour.b * 0xff),
		(uint8_t)(colour.a * 0xff));
	SDL_RenderFillRect(s_sdl_renderer->renderer, &rect);
}
