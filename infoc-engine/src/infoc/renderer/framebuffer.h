#pragma once

#include "infoc/core/defines.h"

#include "texture.h"

typedef struct framebuffer_t
{
	uint32_t framebuffer_handle;
	uint32_t width;
	uint32_t height;

	texture_t* colour_attachments; // darray
	texture_t depth_attachment;

	uint32_t pbos[2];
	uint32_t pbo_index;
} framebuffer_t;

bool framebuffer_create(uint32_t width, uint32_t height, framebuffer_t* out_framebuffer);
void framebuffer_destroy(framebuffer_t* framebuffer);

void framebuffer_bind(framebuffer_t* framebuffer);
void framebuffer_unbind(framebuffer_t* framebuffer);

void framebuffer_add_colour_attachment(framebuffer_t* framebuffer);
void framebuffer_add_attachment(framebuffer_t* framebuffer, uint32_t texture_format);
void framebuffer_attach_texture(framebuffer_t* framebuffer, texture_t* colour_attachment);
void framebuffer_create_depth_attachment(framebuffer_t* framebuffer);

void framebuffer_blit_to_screen(const framebuffer_t* framebuffer, uint32_t screen_width, uint32_t screen_height);
vec4 framebuffer_read_pixel(framebuffer_t* framebuffer, uint32_t attachment_index, uint32_t x, uint32_t y);