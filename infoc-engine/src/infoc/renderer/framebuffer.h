#pragma once

#include "infoc/core/defines.h"

#include "texture.h"

/*
* Framebuffer object
*/
typedef struct framebuffer_t
{
	uint32_t framebuffer_handle; /* OpenGL framebuffer handle */
	uint32_t width; /* Framebuffer width */
	uint32_t height; /* Framebuffer height */

	texture_t* colour_attachments; /* A dynamic array of colour attachments  */
	texture_t depth_attachment; /* Depth attachment (optional) */
} framebuffer_t;

/*
* Creates a framebuffer
*
* @param width The width of the framebuffer
* @param height The height of the framebuffer
* @param out_framebuffer A pointer to a `framebuffer_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool framebuffer_create(uint32_t width, uint32_t height, framebuffer_t* out_framebuffer);
/*
* Destroys a framebuffer
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
*/
void framebuffer_destroy(framebuffer_t* framebuffer);

/*
* Binds a framebuffer
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
*/
void framebuffer_bind(framebuffer_t* framebuffer);
/*
* Unbinds a framebuffer
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
*/
void framebuffer_unbind(framebuffer_t* framebuffer);

/*
* Attaches a colour attachment to a framebuffer
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
*/
void framebuffer_add_colour_attachment(framebuffer_t* framebuffer);
/*
* Attaches a colour attachment to a framebuffer
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
* @param texture_format OpenGL format enum of the attachment
*/
void framebuffer_add_attachment(framebuffer_t* framebuffer, uint32_t texture_format);
/*
* Attaches a colour attachment to a framebuffer
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
* @param colour_attachment A pointer to an existing OpenGL texture to be used as colour attachment
*/
void framebuffer_attach_texture(framebuffer_t* framebuffer, texture_t* colour_attachment);
/*
* Attaches a depth attachment to a framebuffer
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
*/
void framebuffer_create_depth_attachment(framebuffer_t* framebuffer);

/*
* Blits the contents of a framebuffer to the screen
*
* @param framebuffer A pointer to a valid `framebuffer_t` struct
* @param screen_width The width of the screen
* @param screen_height The height of the screen
*/
void framebuffer_blit_to_screen(const framebuffer_t* framebuffer, uint32_t screen_width, uint32_t screen_height);
