#include "framebuffer.h"

#include "infoc/core/darray.h"

#include "gl.h"

#include <stdio.h>
#include <string.h>

bool framebuffer_create(uint32_t width, uint32_t height, framebuffer_t* out_framebuffer)
{
	memset(out_framebuffer, 0, sizeof(framebuffer_t));

	glCreateFramebuffers(1, &out_framebuffer->framebuffer_handle);
	check_error(out_framebuffer->framebuffer_handle == 0, "Failed to create framebuffer!");

	out_framebuffer->width = width;
	out_framebuffer->height = height;
	out_framebuffer->colour_attachments = darray_create(texture_t);

	return true;
}

void framebuffer_destroy(framebuffer_t* framebuffer)
{
	darray_destroy(framebuffer->colour_attachments);
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

	glDrawBuffers((uint32_t)darray_count(renderbuffers), (const GLenum*)renderbuffers);

	if (texture_is_valid(&framebuffer->depth_attachment))
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	darray_destroy(renderbuffers);
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

	check_error_no_return(glCheckNamedFramebufferStatus(framebuffer->framebuffer_handle, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "Framebuffer isn't complete!");
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
