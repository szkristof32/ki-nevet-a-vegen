#include "framebuffer.h"

#include "infoc/core/darray.h"

#include "gl.h"

#include <stdio.h>
#include <string.h>

bool framebuffer_create(uint32_t width, uint32_t height, framebuffer_t* out_framebuffer)
{
	memset(out_framebuffer, 0, sizeof(framebuffer_t));

	glCreateFramebuffers(1, &out_framebuffer->framebuffer_handle);
	if (out_framebuffer->framebuffer_handle == 0)
	{
		fprintf(stderr, "Failed to create framebuffer!\n");
		return false;
	}

	out_framebuffer->width = width;
	out_framebuffer->height = height;
	out_framebuffer->colour_attachments = darray_create(texture_t);

	glCreateBuffers(2, out_framebuffer->pbos);
	if (out_framebuffer->pbos[0] == 0 || out_framebuffer->pbos[1] == 0)
	{
		fprintf(stderr, "Failed to create pbos!\n");
		return false;
	}
	glNamedBufferData(out_framebuffer->pbos[0], width * height * sizeof(uint32_t), NULL, GL_STREAM_READ);
	glNamedBufferData(out_framebuffer->pbos[1], width * height * sizeof(uint32_t), NULL, GL_STREAM_READ);

	return true;
}

void framebuffer_destroy(framebuffer_t* framebuffer)
{
	glDeleteFramebuffers(1, &framebuffer->framebuffer_handle);
	memset(framebuffer, 0, sizeof(framebuffer_t));
}

void framebuffer_bind(framebuffer_t* framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->framebuffer_handle);

	uint32_t* renderbuffers = darray_reserve(uint32_t, darray_count(framebuffer->colour_attachments));
	for (uint32_t i = 0; i < darray_count(framebuffer->colour_attachments); i++)
	{
		uint32_t buf = GL_COLOR_ATTACHMENT0 + i;
		darray_push(renderbuffers, buf);
	}

	if (darray_count(framebuffer->colour_attachments) != 0)
	{
		texture_t* texture = &framebuffer->colour_attachments[0];
		glViewport(0, 0, texture->width, texture->height);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glDrawBuffers((uint32_t)darray_count(renderbuffers), renderbuffers);

	if (texture_is_valid(&framebuffer->depth_attachment))
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
}

void framebuffer_unbind(framebuffer_t* framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void framebuffer_add_colour_attachment(framebuffer_t* framebuffer)
{
	texture_t texture;
	texture_create_empty(framebuffer->width, framebuffer->height, &texture);

	framebuffer_attach_texture(framebuffer, &texture);
}

void framebuffer_add_attachment(framebuffer_t* framebuffer, uint32_t texture_format)
{
	texture_t texture;
	texture_create_format(framebuffer->width, framebuffer->height, texture_format, &texture);

	framebuffer_attach_texture(framebuffer, &texture);
}

void framebuffer_attach_texture(framebuffer_t* framebuffer, texture_t* colour_attachment)
{
	uint32_t attachment_index = (uint32_t)darray_count(framebuffer->colour_attachments);

	glNamedFramebufferTexture(framebuffer->framebuffer_handle, GL_COLOR_ATTACHMENT0 + attachment_index, colour_attachment->texture_handle, 0);
	darray_push(framebuffer->colour_attachments, *colour_attachment);

	if (glCheckNamedFramebufferStatus(framebuffer->framebuffer_handle, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		fprintf(stderr, "Framebuffer isn't complete!\n");
	}
}

void framebuffer_create_depth_attachment(framebuffer_t* framebuffer)
{
	texture_create_depth(framebuffer->width, framebuffer->height, &framebuffer->depth_attachment);

	glNamedFramebufferTexture(framebuffer->framebuffer_handle, GL_DEPTH_STENCIL_ATTACHMENT, framebuffer->depth_attachment.texture_handle, 0);
}

void framebuffer_blit_to_screen(const framebuffer_t* framebuffer, uint32_t screen_width, uint32_t screen_height)
{
	if (darray_count(framebuffer->colour_attachments) == 0)
		return;

	texture_t* texture = &framebuffer->colour_attachments[0];
	glNamedFramebufferReadBuffer(framebuffer->framebuffer_handle, GL_COLOR_ATTACHMENT0);
	glBlitNamedFramebuffer(framebuffer->framebuffer_handle, 0,
		0, 0, texture->width, texture->height,
		0, 0, screen_width, screen_height,
		GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

#define EXTRACT_RED(colour)		((float)((colour >> 0x03) & 0xff) / 255.0f)
#define EXTRACT_GREEN(colour)	((float)((colour >> 0x02) & 0xff) / 255.0f)
#define EXTRACT_BLUE(colour)	((float)((colour >> 0x01) & 0xff) / 255.0f)
#define EXTRACT_ALPHA(colour)	((float)((colour >> 0x00) & 0xff) / 255.0f)

vec4 framebuffer_read_pixel(framebuffer_t* framebuffer, uint32_t attachment_index, uint32_t x, uint32_t y)
{
	if (darray_count(framebuffer->colour_attachments) - 1 > attachment_index)
		return vec4_scalar(0);

	const texture_t* texture = &framebuffer->colour_attachments[attachment_index];
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return vec4_scalar(0);

	glNamedFramebufferReadBuffer(framebuffer->framebuffer_handle, GL_COLOR_ATTACHMENT0 + attachment_index);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, framebuffer->pbos[framebuffer->pbo_index]);

	glReadPixels(0, 0, framebuffer->width, framebuffer->height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	framebuffer->pbo_index = (framebuffer->pbo_index + 1) % 2;

	glBindBuffer(GL_PIXEL_PACK_BUFFER, framebuffer->pbos[framebuffer->pbo_index]);
	uint8_t* mapped = (uint8_t*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
	uint8_t pixel = mapped[x * framebuffer->width + y];
	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);

	return vec4_create(EXTRACT_RED(pixel), EXTRACT_GREEN(pixel), EXTRACT_BLUE(pixel), EXTRACT_ALPHA(pixel));
}
