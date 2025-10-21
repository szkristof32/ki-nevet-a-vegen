#pragma once

#include "game_object.h"

typedef game_object_t camera_t;

mat4 camera_get_view_matrix(camera_t* camera);
