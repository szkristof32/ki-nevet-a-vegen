#pragma once

#include "mesh.h"

bool static_renderer_init();
void static_renderer_shutdown();

void static_renderer_begin_frame();
void static_renderer_end_frame();

void static_renderer_render(mesh_t* mesh);
