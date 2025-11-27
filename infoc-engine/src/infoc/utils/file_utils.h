#pragma once

#include "infoc/core/defines.h"

/**
 * Reads a file from disk
 *
 * @param path The filepath
 *
 * @returns A buffer with the file contents in it
 *
 * @warning The returned buffer should be freed by the caller
 */
char* file_utils_read_file(const char* path);

/**
 * Checks if a file exists
 * 
 * @param path The filepath
 * 
 * @returns A boolean indicating if the file exists
 */
bool file_utils_file_exists(const char* path);
/**
 * Creates a directory if doesn't exist
 * 
 * @param path The directory path
 */
void file_utils_create_directory(const char* path);

/**
 * Gets the list of files in a directory
 * 
 * @param path The directory path
 * 
 * @returns A dynamic array of filepaths
 */
char** file_utils_get_files_in_directory(const char* path);
