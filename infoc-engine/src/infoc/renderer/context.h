#pragma once

#include "infoc/core/defines.h"
#include "infoc/core/window.h"

/**
 * OpenGL context
 */
typedef struct context_t
{
	/** Pointer to the internal data not exposed */
	void* internal_state;
} context_t;

/**
 * Creates an OpenGL context
 *
 * @param window A pointer to a valid `window_t` struct
 * @param out_context A pointer to a `context_t` struct to be filled
 *
 * @returns A boolean indicating whether the operation finished succesfully
 */
bool context_create(const window_t* window, context_t* out_context);
/**
 * Destroys an OpenGL context
 *
 * @param context A pointer to a valid `context_t` struct
 */
void context_destroy(context_t* context);

/**
 * Swaps the buffers on an OpenGL context
 *
 * @param context A pointer to a valid `context_t` struct
 */
void context_swap(const context_t* context);
