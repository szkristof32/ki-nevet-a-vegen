#pragma once

#include "model.h"

#include "infoc/scene/camera.h"

#include "infoc/math/mat4.h"

bool static_renderer_init();
void static_renderer_shutdown();

void static_renderer_begin_frame();
void static_renderer_end_frame();

void static_renderer_set_camera(camera_t* camera);
void static_renderer_set_object_count(uint32_t count);
void static_renderer_render(model_t* model, mat4 transformation_matrix, vec4 colour, uint32_t index, vec4 highlight);
