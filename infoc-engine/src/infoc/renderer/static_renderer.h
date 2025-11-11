#pragma once

#include "model.h"

#include "infoc/scene/camera.h"

#include "infoc/math/mat4.h"

/*
* Initialises the static renderer
*
* @returns A boolean indicating whether the operation finished succesfully
*/
bool static_renderer_init();
/*
* Shuts down the static renderer
*/
void static_renderer_shutdown();

/*
* Prepares the static renderer for frame rendering
*/
void static_renderer_begin_frame();
/*
* Renders the current frame with the static renderer
*/
void static_renderer_end_frame();

/*
* Window resize callback for the static renderer. Should only be called from window
*
* @param width The window width
* @param height The window height
*/
void static_renderer_on_window_resize(uint32_t width, uint32_t height);

/*
* Sets the currently used camera in the static renderer
*
* @param camera A pointer to a valid `camera_t` struct
*/
void static_renderer_set_camera(camera_t* camera);
/*
* Renders a model using the static shader
*
* @param model The model to be rendered
* @param transformation_matrix The transformation of the model
* @param colour The colour of the model
* @param index The index of the model (used for mouse picking)
* @param highlight The highlight colour for the model
*/
void static_renderer_render(model_t* model, mat4 transformation_matrix, vec4 colour, uint32_t index, vec4 highlight);
