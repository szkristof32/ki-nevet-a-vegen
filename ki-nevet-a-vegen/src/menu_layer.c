#include "menu_layer.h"

#include "infoc/core/engine.h"
#include "infoc/core/input.h"

#include "infoc/renderer/sdl_renderer.h"

static void menu_on_ui_render(SDL_Renderer* renderer);
static void menu_on_window_resize(uint32_t width, uint32_t height);

typedef struct menu_layer_t
{
	layer_t* game_layer;
	uint32_t window_width, window_height;
} menu_layer_t;

static layer_t s_layer = { 0 };
static menu_layer_t* s_menu_layer = NULL;

layer_t menu_layer_create(layer_t* game_layer)
{
	arena_allocator_t* allocator = engine_get_allocator();

	s_layer.on_ui_render = menu_on_ui_render;
	s_layer.on_window_resize = menu_on_window_resize;
	s_layer.internal_state = arena_allocator_allocate(allocator, sizeof(menu_layer_t));

	s_menu_layer = (menu_layer_t*)s_layer.internal_state;
	s_menu_layer->game_layer = game_layer;

	return s_layer;
}

const float ui_padding = 15.0f;

void menu_on_ui_render(SDL_Renderer* renderer)
{
	float mouse_x = input_get_mouse_x() * s_menu_layer->window_width;
	float mouse_y = input_get_mouse_y() * s_menu_layer->window_height;

	{
		SDL_SetRenderDrawColorFloat(renderer, 0.2f, 0.2f, 0.2f, 1.0f);

		SDL_FRect rect = { 0 };
		rect.x = 0;
		rect.y = 0;
		rect.w = (float)s_menu_layer->window_width;
		rect.h = (float)s_menu_layer->window_height;
		SDL_RenderFillRect(renderer, &rect);
	}

	float title_width, title_height;
	{
		const char* title = u8"Mensch ärgere Dich nicht";
		sdl_renderer_get_text_size(title, &title_width, &title_height, true);
		sdl_renderer_draw_text(title, (s_menu_layer->window_width - title_width) / 2.0f, 85.0f, true);
	}

	float y = 85.0f + title_height + 170.0f;

	{
		const char* new_game = "New game";
		float width, height;
		sdl_renderer_get_text_size(new_game, &width, &height, false);

		SDL_FRect rect = { 0 };
		rect.w = max(width + 2.0f * ui_padding, 250.0f);
		rect.h = height + 2.0f * ui_padding;
		rect.x = (s_menu_layer->window_width - rect.w) / 2.0f;
		rect.y = y;

		bool hovered =
			mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
			mouse_y >= rect.y && mouse_y <= rect.y + rect.h;

		if (!hovered)
			SDL_SetRenderDrawColorFloat(renderer, 0.87f, 0.74f, 0.54f, 1.0f);
		else
			SDL_SetRenderDrawColorFloat(renderer, 0.92f, 0.79f, 0.59f, 1.0f);

		SDL_RenderFillRect(renderer, &rect);

		sdl_renderer_draw_text(new_game, (s_menu_layer->window_width - width) / 2.0f, rect.y + ui_padding, false);

		if (hovered && input_is_mouse_button_released(mouse_button_left))
		{
			engine_detach_layer(&s_layer);
			engine_attach_layer(s_menu_layer->game_layer);
		}

		y += rect.h + 2.0f * ui_padding;
	}

	{
		const char* exit = "Exit";
		float width, height;
		sdl_renderer_get_text_size(exit, &width, &height, false);

		SDL_FRect rect = { 0 };
		rect.w = max(width + 2.0f * ui_padding, 250.0f);
		rect.h = height + 2.0f * ui_padding;
		rect.x = (s_menu_layer->window_width - rect.w) / 2.0f;
		rect.y = y;

		bool hovered =
			mouse_x >= rect.x && mouse_x <= rect.x + rect.w &&
			mouse_y >= rect.y && mouse_y <= rect.y + rect.h;

		if (!hovered)
			SDL_SetRenderDrawColorFloat(renderer, 0.87f, 0.74f, 0.54f, 1.0f);
		else
			SDL_SetRenderDrawColorFloat(renderer, 0.92f, 0.79f, 0.59f, 1.0f);

		SDL_RenderFillRect(renderer, &rect);

		sdl_renderer_draw_text(exit, (s_menu_layer->window_width - width) / 2.0f, rect.y + ui_padding, false);

		if (hovered && input_is_mouse_button_released(mouse_button_left))
		{
			engine_request_close();
		}

		y += rect.h + 2.0f * ui_padding;
	}
}

void menu_on_window_resize(uint32_t width, uint32_t height)
{
	s_menu_layer->window_width = width;
	s_menu_layer->window_height = height;
}
