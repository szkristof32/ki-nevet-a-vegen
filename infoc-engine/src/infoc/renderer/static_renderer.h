#pragma once

#include "model.h"

bool static_renderer_init();
void static_renderer_shutdown();

void static_renderer_begin_frame();
void static_renderer_end_frame();

void static_renderer_render(model_t* model);
