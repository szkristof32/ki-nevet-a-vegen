#pragma once

#include "infoc/core/defines.h"

// The caller should free the returned buffer
char* file_utils_read_file(const char* path);
