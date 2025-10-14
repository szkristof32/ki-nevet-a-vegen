#include "gl.h"

#include "infoc/core/engine.h"

#include <SDL3/SDL.h>

#undef bool

typedef void (*pfn_glClear)(GLbitfield);
typedef void (*pfn_glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);

typedef struct gl_t
{
	pfn_glClear glClear;
	pfn_glClearColor glClearColor;
} gl_t;

static gl_t* s_opengl;

#define LOAD_OPENGL_PROC(proc) s_opengl->proc = (pfn_##proc)SDL_GL_GetProcAddress(#proc)

bool opengl_init()
{
	arena_allocator_t* allocator = engine_get_allocator();
	s_opengl = arena_allocator_allocate(allocator, sizeof(gl_t));
	if (s_opengl == NULL)
	{
		fprintf(stderr, "Failed to initialise OpenGL!\n");
		return false;
	}

	SDL_GL_LoadLibrary("opengl32");

	LOAD_OPENGL_PROC(glClear);
	LOAD_OPENGL_PROC(glClearColor);

	return true;
}

void opengl_shutdown()
{
	SDL_GL_UnloadLibrary();

	s_opengl = NULL;
}

void glClear(GLbitfield mask)
{
	s_opengl->glClear(mask);
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	s_opengl->glClearColor(red, green, blue, alpha);
}
