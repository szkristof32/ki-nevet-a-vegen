#include "gl.h"

#include "infoc/core/engine.h"

#include <SDL3/SDL.h>
#include <stdio.h>

#undef bool

typedef void (*pfn_glEnable)(GLenum cap);
typedef void (*pfn_glDisable)(GLenum cap);
typedef void (*pfn_glDebugMessageControl)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
typedef void (*pfn_glDebugMessageCallback)(GLDEBUGPROC callback, const void* userParam);
typedef void (*pfn_glClear)(GLbitfield);
typedef void (*pfn_glClearColor)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (*pfn_glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
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
typedef GLuint(*pfn_glCreateProgram)();
typedef void (*pfn_glDeleteProgram)(GLuint program);
typedef GLuint(*pfn_glCreateShader)(GLenum shaderType);
typedef void (*pfn_glDeleteShader)(GLuint shader);
typedef void (*pfn_glAttachShader)(GLuint program, GLuint shader);
typedef void (*pfn_glDetachShader)(GLuint program, GLuint shader);
typedef void (*pfn_glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef void (*pfn_glCompileShader)(GLuint shader);
typedef void (*pfn_glLinkProgram)(GLuint program);
typedef void (*pfn_glUseProgram)(GLuint program);
typedef void (*pfn_glBindBufferBase)(GLenum target, GLuint index, GLuint buffer);
typedef void (*pfn_glCreateTextures)(GLenum target, GLsizei n, GLuint* textures);
typedef void (*pfn_glDeleteTextures)(GLsizei n, const GLuint* textures);
typedef void (*pfn_glBindTextureUnit)(GLuint unit, GLuint texture);
typedef void (*pfn_glTextureStorage2D)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (*pfn_glTextureSubImage2D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
typedef void (*pfn_glTextureParameteri)(GLuint texture, GLenum pname, GLint param);
typedef void (*pfn_glCreateFramebuffers)(GLsizei n, GLuint* framebuffers);
typedef void (*pfn_glDeleteFramebuffers)(GLsizei n, const GLuint* framebuffers);
typedef void (*pfn_glBindFramebuffer)(GLenum target, GLuint framebuffer);
typedef void (*pfn_glNamedFramebufferTexture)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef GLenum(*pfn_glCheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
typedef void (*pfn_glBlitNamedFramebuffer)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (*pfn_glDrawBuffers)(GLsizei n, const GLenum* bufs);
typedef void (*pfn_glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
typedef void (*pfn_glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void (*pfn_glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
typedef void (*pfn_glNamedFramebufferReadBuffer)(GLuint framebuffer, GLenum src);
typedef void* (*pfn_glMapBuffer)(GLenum target, GLenum access);
typedef GLboolean(*pfn_glUnmapBuffer)(GLenum target);
typedef void (*pfn_glGetTextureSubImage)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels);

typedef struct gl_t
{
	pfn_glEnable glEnable;
	pfn_glDisable glDisable;
	pfn_glDebugMessageControl glDebugMessageControl;
	pfn_glDebugMessageCallback glDebugMessageCallback;
	pfn_glClear glClear;
	pfn_glClearColor glClearColor;
	pfn_glViewport glViewport;
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
	pfn_glBindBufferBase glBindBufferBase;
	pfn_glCreateTextures glCreateTextures;
	pfn_glDeleteTextures glDeleteTextures;
	pfn_glBindTextureUnit glBindTextureUnit;
	pfn_glTextureStorage2D glTextureStorage2D;
	pfn_glTextureSubImage2D glTextureSubImage2D;
	pfn_glTextureParameteri glTextureParameteri;
	pfn_glCreateFramebuffers glCreateFramebuffers;
	pfn_glDeleteFramebuffers glDeleteFramebuffers;
	pfn_glBindFramebuffer glBindFramebuffer;
	pfn_glNamedFramebufferTexture glNamedFramebufferTexture;
	pfn_glCheckNamedFramebufferStatus glCheckNamedFramebufferStatus;
	pfn_glBlitNamedFramebuffer glBlitNamedFramebuffer;
	pfn_glDrawBuffers glDrawBuffers;
	pfn_glGetProgramiv glGetProgramiv;
	pfn_glGetProgramInfoLog glGetProgramInfoLog;
	pfn_glReadPixels glReadPixels;
	pfn_glNamedFramebufferReadBuffer glNamedFramebufferReadBuffer;
	pfn_glMapBuffer glMapBuffer;
	pfn_glUnmapBuffer glUnmapBuffer;
	pfn_glGetTextureSubImage glGetTextureSubImage;
} gl_t;

static gl_t* s_opengl;

#define LOAD_OPENGL_PROC(proc) s_opengl->proc = (pfn_##proc)SDL_GL_GetProcAddress(#proc)

static void opengl_debug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

bool opengl_init()
{
	arena_allocator_t* allocator = engine_get_allocator();
	s_opengl = arena_allocator_allocate(allocator, sizeof(gl_t));
	check_error(s_opengl == NULL, "Failed to initialise OpenGL!");

	SDL_GL_LoadLibrary("opengl32");

	LOAD_OPENGL_PROC(glEnable);
	LOAD_OPENGL_PROC(glDisable);
	LOAD_OPENGL_PROC(glDebugMessageControl);
	LOAD_OPENGL_PROC(glDebugMessageCallback);
	LOAD_OPENGL_PROC(glClear);
	LOAD_OPENGL_PROC(glClearColor);
	LOAD_OPENGL_PROC(glViewport);
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
	LOAD_OPENGL_PROC(glBindBufferBase);
	LOAD_OPENGL_PROC(glCreateTextures);
	LOAD_OPENGL_PROC(glDeleteTextures);
	LOAD_OPENGL_PROC(glBindTextureUnit);
	LOAD_OPENGL_PROC(glTextureStorage2D);
	LOAD_OPENGL_PROC(glTextureSubImage2D);
	LOAD_OPENGL_PROC(glTextureParameteri);
	LOAD_OPENGL_PROC(glCreateFramebuffers);
	LOAD_OPENGL_PROC(glDeleteFramebuffers);
	LOAD_OPENGL_PROC(glBindFramebuffer);
	LOAD_OPENGL_PROC(glNamedFramebufferTexture);
	LOAD_OPENGL_PROC(glCheckNamedFramebufferStatus);
	LOAD_OPENGL_PROC(glBlitNamedFramebuffer);
	LOAD_OPENGL_PROC(glDrawBuffers);
	LOAD_OPENGL_PROC(glGetProgramiv);
	LOAD_OPENGL_PROC(glGetProgramInfoLog);
	LOAD_OPENGL_PROC(glReadPixels);
	LOAD_OPENGL_PROC(glNamedFramebufferReadBuffer);
	LOAD_OPENGL_PROC(glMapBuffer);
	LOAD_OPENGL_PROC(glUnmapBuffer);
	LOAD_OPENGL_PROC(glGetTextureSubImage);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(opengl_debug, NULL);

	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, false);

	return true;
}

void opengl_shutdown()
{
	SDL_GL_UnloadLibrary();

	s_opengl = NULL;
}

void opengl_debug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	switch ((uint32_t)severity)
	{
		case GL_DEBUG_SEVERITY_NOTIFICATION:	printf("[OpenGL notification] %s\n", message); return;
		case GL_DEBUG_SEVERITY_LOW:				printf("[OpenGL information] %s\n", message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:			printf("[OpenGL warning] %s\n", message); return;
		case GL_DEBUG_SEVERITY_HIGH:			log_error("[OpenGL error] %s", message); return;
	}
}

void glEnable(GLenum cap)
{
	s_opengl->glEnable(cap);
}

void glDisable(GLenum cap)
{
	s_opengl->glDisable(cap);
}

void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled)
{
	s_opengl->glDebugMessageControl(source, type, severity, count, ids, enabled);
}

void glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam)
{
	s_opengl->glDebugMessageCallback(callback, userParam);
}

void glClear(GLbitfield mask)
{
	s_opengl->glClear(mask);
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	s_opengl->glClearColor(red, green, blue, alpha);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	s_opengl->glViewport(x, y, width, height);
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

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	s_opengl->glBindBufferBase(target, index, buffer);
}

void glCreateTextures(GLenum target, GLsizei n, GLuint* textures)
{
	s_opengl->glCreateTextures(target, n, textures);
}

void glDeleteTextures(GLsizei n, const GLuint* textures)
{
	s_opengl->glDeleteTextures(n, textures);
}

void glBindTextureUnit(GLuint unit, GLuint texture)
{
	s_opengl->glBindTextureUnit(unit, texture);
}

void glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	s_opengl->glTextureStorage2D(texture, levels, internalformat, width, height);
}

void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels)
{
	s_opengl->glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
}

void glTextureParameteri(GLuint texture, GLenum pname, GLint param)
{
	s_opengl->glTextureParameteri(texture, pname, param);
}

void glCreateFramebuffers(GLsizei n, GLuint* framebuffers)
{
	s_opengl->glCreateFramebuffers(n, framebuffers);
}

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	s_opengl->glDeleteFramebuffers(n, framebuffers);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	s_opengl->glBindFramebuffer(target, framebuffer);
}

void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
{
	s_opengl->glNamedFramebufferTexture(framebuffer, attachment, texture, level);
}

GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
{
	return s_opengl->glCheckNamedFramebufferStatus(framebuffer, target);
}

void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	s_opengl->glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void glDrawBuffers(GLsizei n, const GLenum* bufs)
{
	s_opengl->glDrawBuffers(n, bufs);
}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	s_opengl->glGetProgramiv(program, pname, params);
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	s_opengl->glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
{
	s_opengl->glReadPixels(x, y, width, height, format, type, pixels);
}

void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
{
	s_opengl->glNamedFramebufferReadBuffer(framebuffer, src);
}

void* glMapBuffer(GLenum target, GLenum access)
{
	return s_opengl->glMapBuffer(target, access);
}

GLboolean glUnmapBuffer(GLenum target)
{
	return s_opengl->glUnmapBuffer(target);
}

void glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
	s_opengl->glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
}
