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
typedef void (*pfn_glCreateVertexArrays)(GLsizei, GLuint*);
typedef void (*pfn_glDeleteVertexArrays)(GLsizei, GLuint*);
typedef void (*pfn_glBindVertexArray)(GLuint);
typedef void (*pfn_glEnableVertexAttribArray)(GLuint);
typedef void (*pfn_glVertexAttribPointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*pfn_glVertexAttribIPointer)(GLuint, GLint, GLenum, GLsizei, const void*);
typedef void (*pfn_glDrawArrays)(GLenum, GLint, GLsizei);
typedef void (*pfn_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indices);
typedef GLuint (*pfn_glCreateProgram)();
typedef void (*pfn_glDeleteProgram)(GLuint program);
typedef GLuint (*pfn_glCreateShader)(GLenum shaderType);
typedef void (*pfn_glDeleteShader)(GLuint shader);
typedef void (*pfn_glAttachShader)(GLuint program, GLuint shader);
typedef void (*pfn_glDetachShader)(GLuint program, GLuint shader);
typedef void (*pfn_glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef void (*pfn_glCompileShader)(GLuint shader);
typedef void (*pfn_glLinkProgram)(GLuint program);
typedef void (*pfn_glUseProgram)(GLuint program);

typedef struct gl_t
{
	pfn_glClear glClear;
	pfn_glClearColor glClearColor;
	pfn_glCreateBuffers glCreateBuffers;
	pfn_glDeleteBuffers glDeleteBuffers;
	pfn_glBindBuffer glBindBuffer;
	pfn_glNamedBufferData glNamedBufferData;
	pfn_glNamedBufferSubData glNamedBufferSubData;
	pfn_glCreateVertexArrays glCreateVertexArrays;
	pfn_glDeleteVertexArrays glDeleteVertexArrays;
	pfn_glBindVertexArray glBindVertexArray;
	pfn_glEnableVertexAttribArray glEnableVertexAttribArray;
	pfn_glVertexAttribPointer glVertexAttribPointer;
	pfn_glVertexAttribIPointer glVertexAttribIPointer;
	pfn_glDrawArrays glDrawArrays;
	pfn_glDrawElements glDrawElements;
pfn_glCreateProgram glCreateProgram;
	pfn_glDeleteProgram glDeleteProgram;
	pfn_glCreateShader glCreateShader;
	pfn_glDeleteShader glDeleteShader;
	pfn_glAttachShader glAttachShader;
	pfn_glDetachShader glDetachShader;
	pfn_glShaderSource glShaderSource;
	pfn_glCompileShader glCompileShader;
	pfn_glLinkProgram glLinkProgram;
	pfn_glUseProgram glUseProgram;
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
	LOAD_OPENGL_PROC(glCreateVertexArrays);
	LOAD_OPENGL_PROC(glDeleteVertexArrays);
	LOAD_OPENGL_PROC(glBindVertexArray);
	LOAD_OPENGL_PROC(glEnableVertexAttribArray);
	LOAD_OPENGL_PROC(glVertexAttribPointer);
	LOAD_OPENGL_PROC(glVertexAttribIPointer);
	LOAD_OPENGL_PROC(glDrawArrays);
	LOAD_OPENGL_PROC(glDrawElements);
	LOAD_OPENGL_PROC(glCreateProgram);
	LOAD_OPENGL_PROC(glDeleteProgram);
	LOAD_OPENGL_PROC(glCreateShader);
	LOAD_OPENGL_PROC(glDeleteShader);
	LOAD_OPENGL_PROC(glAttachShader);
	LOAD_OPENGL_PROC(glDetachShader);
	LOAD_OPENGL_PROC(glShaderSource);
	LOAD_OPENGL_PROC(glCompileShader);
	LOAD_OPENGL_PROC(glLinkProgram);
	LOAD_OPENGL_PROC(glUseProgram);

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

void glCreateVertexArrays(GLsizei n, GLuint* arrays)
{
	s_opengl->glCreateVertexArrays(n, arrays);
}

void glDeleteVertexArrays(GLsizei n, GLuint* arrays)
{
	s_opengl->glDeleteVertexArrays(n, arrays);
}

void glBindVertexArray(GLuint array)
{
	s_opengl->glBindVertexArray(array);
}

void glEnableVertexAttribArray(GLuint index)
{
	s_opengl->glEnableVertexAttribArray(index);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	s_opengl->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer)
{
	s_opengl->glVertexAttribIPointer(index, size, type, stride, pointer);
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	s_opengl->glDrawArrays(mode, first, count);
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices)
{
	s_opengl->glDrawElements(mode, count, type, indices);
}

GLuint glCreateProgram()
{
	return s_opengl->glCreateProgram();
}

void glDeleteProgram(GLuint program)
{
	s_opengl->glDeleteProgram(program);
}

GLuint glCreateShader(GLenum shaderType)
{
	return s_opengl->glCreateShader(shaderType);
}

void glDeleteShader(GLuint shader)
{
	s_opengl->glDeleteShader(shader);
}

void glAttachShader(GLuint program, GLuint shader)
{
	s_opengl->glAttachShader(program, shader);
}

void glDetachShader(GLuint program, GLuint shader)
{
	s_opengl->glDetachShader(program, shader);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
{
	s_opengl->glShaderSource(shader, count, string, length);
}

void glCompileShader(GLuint shader)
{
	s_opengl->glCompileShader(shader);
}

void glLinkProgram(GLuint program)
{
	s_opengl->glLinkProgram(program);
}

void glUseProgram(GLuint program)
{
	s_opengl->glUseProgram(program);
}
