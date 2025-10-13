#include "context.h"

#include "infoc/core/engine.h"

#include "infoc/renderer/gl.h"

#include <SDL3/SDL.h>

#undef bool

typedef struct context_internal_t
{
	SDL_Window* window_handle;
	SDL_GLContext opengl_context;
} context_internal_t;

bool context_create(const window_t* window, context_t* out_context)
{
	memset(out_context, 0, sizeof(context_t));

	arena_allocator_t* allocator = engine_get_allocator();
	context_internal_t* internal_state = arena_allocator_allocate(allocator, sizeof(context_internal_t));
	if (internal_state == NULL)
	{
		fprintf(stderr, "Failed to allocate context internal state!\n");
		return false;
	}

	out_context->internal_state = internal_state;

	internal_state->window_handle = window_get_handle(window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	internal_state->opengl_context = SDL_GL_CreateContext(internal_state->window_handle);
	if (!internal_state->opengl_context)
	{
		fprintf(stderr, "Failed to create OpenGL context (%s)!\n", SDL_GetError());
		return false;
	}

	if (!SDL_GL_MakeCurrent(internal_state->window_handle, internal_state->opengl_context))
	{
		fprintf(stderr, "Failed to make context current (%s)!\n", SDL_GetError());
		return false;
	}

	if (!opengl_init())
	{
		fprintf(stderr, "Failed to initialise OpenGL!\n");
		return false;
	}

	return true;
}

void context_destroy(context_t* context)
{
	opengl_shutdown();

	context_internal_t* internal_state = context->internal_state;
	SDL_GL_DestroyContext(internal_state->opengl_context);

	memset(context, 0, sizeof(context_t));
}

void context_swap(const context_t* context)
{
	context_internal_t* internal_state = context->internal_state;
	SDL_GL_SwapWindow(internal_state->window_handle);
}
