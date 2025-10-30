#pragma once

#include "infoc/core/defines.h"

bool opengl_init();
void opengl_shutdown();

typedef unsigned char GLboolean;
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
	GL_FALSE = 0,
	GL_TRUE = 1,

	GL_TRIANGLES = 0x0004,
	GL_TRIANGLE_STRIP = 0x0005,
	GL_TRIANGLE_FAN = 0x0006,

	GL_DEPTH_TEST = 0x0B71,

	GL_TEXTURE_2D = 0x0DE1,

	GL_DONT_CARE = 0x1100,

	GL_BYTE = 0x1400,
	GL_UNSIGNED_BYTE = 0x1401,
	GL_SHORT = 0x1402,
	GL_UNSIGNED_SHORT = 0x1403,
	GL_INT = 0x1404,
	GL_UNSIGNED_INT = 0x1405,
	GL_FLOAT = 0x1406,
	GL_DOUBLE = 0x1407,

	GL_NEAREST = 0x2600,
	GL_LINEAR = 0x2601,

	GL_TEXTURE_MAG_FILTER = 0x2800,
	GL_TEXTURE_MIN_FILTER = 0x2801,
	GL_TEXTURE_WRAP_S = 0x2802,
	GL_TEXTURE_WRAP_T = 0x2803,

	GL_REPEAT = 0x2901,

	GL_RED = 0x1903,
	GL_RGB = 0x1907,
	GL_RGBA = 0x1908,

	GL_RGB8 = 0x8051,
	GL_RGBA8 = 0x8058,

	GL_BGR = 0x80E0,
	GL_BGRA = 0x80E1,

	GL_R32UI = 0x8236,
	GL_RED_INTEGER = 0x8D94,

	GL_READ_ONLY = 0x88B8,
	GL_WRITE_ONLY = 0x88B9,

	GL_DEPTH24_STENCIL8 = 0x88F0,
	GL_DEPTH_STENCIL = 0x84F9,

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

	GL_FRAGMENT_SHADER = 0x8B30,
	GL_VERTEX_SHADER = 0x8B31,
	GL_COMPUTE_SHADER = 0x91B9,

	GL_LINK_STATUS = 0x8B82,

	GL_FRAMEBUFFER_COMPLETE = 0x8CD5,

	GL_DEPTH_STENCIL_ATTACHMENT = 0x821A,
	GL_COLOR_ATTACHMENT0 = 0x8CE0,
	GL_COLOR_ATTACHMENT1 = 0x8CE1,
	GL_COLOR_ATTACHMENT2 = 0x8CE2,
	GL_COLOR_ATTACHMENT3 = 0x8CE3,
	GL_COLOR_ATTACHMENT4 = 0x8CE4,
	GL_COLOR_ATTACHMENT5 = 0x8CE5,
	GL_COLOR_ATTACHMENT6 = 0x8CE6,
	GL_COLOR_ATTACHMENT7 = 0x8CE7,
	GL_COLOR_ATTACHMENT8 = 0x8CE8,
	GL_COLOR_ATTACHMENT9 = 0x8CE9,
	GL_COLOR_ATTACHMENT10 = 0x8CEA,
	GL_COLOR_ATTACHMENT11 = 0x8CEB,
	GL_COLOR_ATTACHMENT12 = 0x8CEC,
	GL_COLOR_ATTACHMENT13 = 0x8CED,
	GL_COLOR_ATTACHMENT14 = 0x8CEE,
	GL_COLOR_ATTACHMENT15 = 0x8CEF,
	GL_COLOR_ATTACHMENT16 = 0x8CF0,
	GL_COLOR_ATTACHMENT17 = 0x8CF1,
	GL_COLOR_ATTACHMENT18 = 0x8CF2,
	GL_COLOR_ATTACHMENT19 = 0x8CF3,
	GL_COLOR_ATTACHMENT20 = 0x8CF4,
	GL_COLOR_ATTACHMENT21 = 0x8CF5,
	GL_COLOR_ATTACHMENT22 = 0x8CF6,
	GL_COLOR_ATTACHMENT23 = 0x8CF7,
	GL_COLOR_ATTACHMENT24 = 0x8CF8,
	GL_COLOR_ATTACHMENT25 = 0x8CF9,
	GL_COLOR_ATTACHMENT26 = 0x8CFA,
	GL_COLOR_ATTACHMENT27 = 0x8CFB,
	GL_COLOR_ATTACHMENT28 = 0x8CFC,
	GL_COLOR_ATTACHMENT29 = 0x8CFD,
	GL_COLOR_ATTACHMENT30 = 0x8CFE,
	GL_COLOR_ATTACHMENT31 = 0x8CFF,

	GL_FRAMEBUFFER = 0x8D40,

	GL_PIXEL_PACK_BUFFER = 0x88EB,
	GL_PIXEL_UNPACK_BUFFER = 0x88EC,

	GL_DEBUG_SEVERITY_HIGH = 0x9146,
	GL_DEBUG_SEVERITY_MEDIUM = 0x9147,
	GL_DEBUG_SEVERITY_LOW = 0x9148,
	GL_DEBUG_SEVERITY_NOTIFICATION = 0x826B,

	GL_DEBUG_OUTPUT = 0x92E0,
	GL_DEBUG_OUTPUT_SYNCHRONOUS = 0x8242,
} GLenum;

typedef void (*GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

void glEnable(GLenum cap);
void glDisable(GLenum cap);
void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint* ids, GLboolean enabled);
void glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam);
void glClear(GLbitfield mask);
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
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
void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
GLuint glCreateProgram();
void glDeleteProgram(GLuint program);
GLuint glCreateShader(GLenum shaderType);
void glDeleteShader(GLuint shader);
void glAttachShader(GLuint program, GLuint shader);
void glDetachShader(GLuint program, GLuint shader);
void glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
void glCompileShader(GLuint shader);
void glLinkProgram(GLuint program);
void glUseProgram(GLuint program);
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer);
void glCreateTextures(GLenum target, GLsizei n, GLuint* textures);
void glDeleteTextures(GLsizei n, const GLuint* textures);
void glBindTextureUnit(GLuint unit, GLuint texture);
void glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
void glTextureParameteri(GLuint texture, GLenum pname, GLint param);
void glCreateFramebuffers(GLsizei n, GLuint* framebuffers);
void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers);
void glBindFramebuffer(GLenum target, GLuint framebuffer);
void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target);
void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
void glDrawBuffers(GLsizei n, const GLenum* bufs);
void glGetProgramiv(GLuint program, GLenum pname, GLint* params);
void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src);
void* glMapBuffer(GLenum target, GLenum access);
GLboolean glUnmapBuffer(GLenum target);
void glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void* pixels);
