#pragma once

#include "infoc/core/defines.h"

bool opengl_init();
void opengl_shutdown();

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef float GLfloat;
typedef double GLdouble;
typedef char GLchar;
typedef unsigned short GLhalf;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef int64_t GLint64;
typedef uint64_t GLuint64;

typedef enum GLbitfield
{
	GL_DEPTH_BUFFER_BIT = 0x00000100,
	GL_STENCIL_BUFFER_BIT = 0x00000400,
	GL_COLOR_BUFFER_BIT = 0x00004000,
} GLbitfield;

typedef enum GLenum
{
	GL_TRIANGLES = 0x0004,
	GL_TRIANGLE_STRIP = 0x0005,
	GL_TRIANGLE_FAN = 0x0006,

	GL_BYTE = 0x1400,
	GL_UNSIGNED_BYTE = 0x1401,
	GL_SHORT = 0x1402,
	GL_UNSIGNED_SHORT = 0x1403,
	GL_INT = 0x1404,
	GL_UNSIGNED_INT = 0x1405,
	GL_FLOAT = 0x1406,
	GL_DOUBLE = 0x1407,

	GL_ARRAY_BUFFER = 0x8892,
	GL_ELEMENT_ARRAY_BUFFER = 0x8893,
	GL_UNIFORM_BUFFER = 0x8A11,

	GL_STREAM_DRAW = 0x88E0,
	GL_STREAM_READ = 0x88E1,
	GL_STREAM_COPY = 0x88E2,
	GL_STATIC_DRAW = 0x88E4,
	GL_STATIC_READ = 0x88E5,
	GL_STATIC_COPY = 0x88E6,
	GL_DYNAMIC_DRAW = 0x88E8,
	GL_DYNAMIC_READ = 0x88E9,
	GL_DYNAMIC_COPY = 0x88EA,
} GLenum;

void glClear(GLbitfield mask);
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void glCreateBuffers(GLsizei n, GLuint* buffers);
void glDeleteBuffers(GLsizei n, GLuint* buffers);
void glBindBuffer(GLenum target, GLuint buffer);
void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage);
void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
void glCreateVertexArrays(GLsizei n, GLuint* arrays);
void glDeleteVertexArrays(GLsizei n, GLuint* arrays);
void glBindVertexArray(GLuint array);
void glEnableVertexAttribArray(GLuint index);
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
void glDrawArrays(GLenum mode, GLint first, GLsizei count);
