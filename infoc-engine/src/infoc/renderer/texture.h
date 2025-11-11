#pragma once

#include "infoc/core/defines.h"

#include "infoc/math/vec4.h"

/*
* Texture
*/
typedef struct texture_t
{
	uint32_t texture_handle; /* OpenGL texture handle */
	uint32_t width; /* Texture width */
	uint32_t height; /* Texture height */
	bool is_depth; /* Boolean indicating if texture is a depth texture */
} texture_t;

/*
* Loads an image from disk
*
* @param filepath The filepath of the image
* @param out_texture A pointer to a `texture_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool texture_create(const char* filepath, texture_t* out_texture);
/*
* Creates an empty texture
*
* @param width The width of the texture
* @param height The height of the texture
* @param out_texture A pointer to a `textuer_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool texture_create_empty(uint32_t width, uint32_t height, texture_t* out_texture);
/*
* Creates an empty texture
*
* @param width The width of the texture
* @param height The height of the texture
* @param format The OpenGL format enum of the texture
* @param out_texture A pointer to a `textuer_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool texture_create_format(uint32_t width, uint32_t height, uint32_t format, texture_t* out_texture);
/*
* Creates an empty depth texture
*
* @param width The width of the texture
* @param height The height of the texture
* @param out_texture A pointer to a `textuer_t` struct to be filled
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool texture_create_depth(uint32_t width, uint32_t height, texture_t* out_texture);
/*
* Destroys a texture
*
* @param texture A pointer to a valid `textuer_t` struct
*/
void texture_destroy(texture_t* texture);

/*
* Binds a texture
*
* @param texture A pointer to a valid `texture_t` struct
* @param texture_unit The texture unit to be bound into
*/
void texture_bind(const texture_t* texture, uint32_t texture_unit);

/*
* Stores data into the texture
*
* @param texture A pointer to a valid `texture_t` struct
* @param data The data to be stored (must be the entire textue)
*/
void texture_set_data(const texture_t* texture, const void* data);
/*
* Stores data into the texture
*
* @param texture A pointer to a valid `texture_t` struct
* @param data The data to be stored (must be the entire textue)
* @param format OpenGL format enum which the data is presented in
*/
void texture_set_data_format(const texture_t* texture, const void* data, uint32_t format);

/*
* Checks if a texture exists
*
* @param texture A pointer to a valid `texture_t` struct
*
* @returns A boolean indicating if the texture exists
*/
bool texture_is_valid(const texture_t* texture);

/*
* Reads the pixel value of a texture at a given point
*
* @param texture A pointer to a valid `texture_t` struct
* @param x, y The pixel coordinates
*
* @returns The colour value at the pixel
*/
vec4 texture_read_pixel(texture_t* texture, uint32_t x, uint32_t y);
/*
* Reads the pixel value of a texture at a given point
*
* @param texture A pointer to a valid `texture_t` struct
* @param x, y The pixel coordinates
*
* @returns The value at the pixel
*/
uint32_t texture_read_pixel_uint(texture_t* texture, uint32_t x, uint32_t y);
