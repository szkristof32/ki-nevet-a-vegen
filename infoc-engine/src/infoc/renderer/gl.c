#include "gl.h"

#include "infoc/core/engine.h"

#include <SDL3/SDL.h>

#undef bool

typedef void (*pfn_glClear)(GLbitfield);
typedef void (*pfn_glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (*pfn_glCreateBuffers)(GLsizei, GLuint*);
typedef void (*pfn_glDeleteBuffers)(GLsizei, GLuint*);
typedef void (*pfn_glBindBuffer)(GLenum, GLuint);
typedef void (*pfn_glNamedBufferData)(GLuint, GLsizeiptr, const void*, GLenum);
typedef void (*pfn_glNamedBufferSubData)(GLuint, GLintptr, GLsizeiptr, const void*);

typedef struct gl_t
{
	pfn_glClear glClear;
	pfn_glClearColor glClearColor;
	pfn_glCreateBuffers glCreateBuffers;
	pfn_glDeleteBuffers glDeleteBuffers;
	pfn_glBindBuffer glBindBuffer;
	pfn_glNamedBufferData glNamedBufferData;
	pfn_glNamedBufferSubData glNamedBufferSubData;
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
	LOAD_OPENGL_PROC(glCreateBuffers);
	LOAD_OPENGL_PROC(glDeleteBuffers);
	LOAD_OPENGL_PROC(glBindBuffer);
	LOAD_OPENGL_PROC(glNamedBufferData);
	LOAD_OPENGL_PROC(glNamedBufferSubData);

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

void glCreateBuffers(GLsizei n, GLuint* buffers)
{
	s_opengl->glCreateBuffers(n, buffers);
}

void glDeleteBuffers(GLsizei n, GLuint* buffers)
{
	s_opengl->glDeleteBuffers(n, buffers);
}

void glBindBuffer(GLenum target, GLuint buffer)
{
	s_opengl->glBindBuffer(target, buffer);
}

void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage)
{
	s_opengl->glNamedBufferData(buffer, size, data, usage);
}

void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data)
{
	s_opengl->glNamedBufferSubData(buffer, offset, size, data);
}
