#pragma once

#include "infoc/core/defines.h"

#include <wchar.h>

/*
* Checks if a string starts with a given character sequence
*
* @param str The string to be checked
* @param beg The starting sequence
*
* @returns A boolean indicating whether `str` strarts with `beg`
*/
bool string_starts_with(const char* str, const char* beg);

/*
* Splits a string by a delimeter
*
* @param str The source string
* @param delim The delimeter
*
* @returns A dynamic array of the string parts
*
* @warning Since the function returns a darray, after use it should be freed with `darray_destroy`
*/
char** string_split(char* str, const char* delim);

wchar_t* string_to_wstring(const char* str);
