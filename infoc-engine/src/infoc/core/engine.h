#pragma once

#include "defines.h"
#include "arena_allocator.h"
#include "window.h"
#include "layers.h"

/**
 * Initialises the core engine
 *
 * @returns A boolean inidicating whether the operation finished succesfully
 */
bool engine_initialise();
/**
 * Shuts down the engine
 */
void engine_shutdown();

/**
 * Starts the main loop of the engine. Runs as long as the application is running
 */
void engine_run();

/**
 * Requests the application to close
 */
void engine_request_close();
/**
 * Pushes a layer to the layer stack of the engine
 *
 * @param layer A pointer to the layer to be pushed onto the stack
 */
void engine_attach_layer(layer_t* layer);
/**
 * Pops a layer from the layer stack of the engine
 *
 * @param layer a pointer to the layer to be removed from the stack
 */
void engine_detach_layer(layer_t* layer);

/**
 * Window resize callback. Should only be called by the window handler
 *
 * @param width The new width of the window
 * @param height The new height of the window
 */
void engine_on_window_resize(uint32_t width, uint32_t height);

/**
 * Gets the arena allocator of the core engine
 *
 * @returns A pointer to the arena allocator
 */
arena_allocator_t* engine_get_allocator();
window_t* engine_get_window();
/**
 * Gets the default texture to be used in rendering
 *
 * @returns A pointer to the texture
 */
struct texture_t* engine_get_default_texture();
