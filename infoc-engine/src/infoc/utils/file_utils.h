#pragma once

#include "infoc/core/defines.h"

/*
* Reads a file from disk
*
* @param path The filepath
*
* @returns A buffer with the file contents in it
*
* @warning The returned buffer should be freed by the caller
*/
char* file_utils_read_file(const char* path);

bool file_utils_file_exists(const char* path);
void file_utils_create_directory(const char* path);
