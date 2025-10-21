#pragma once

#include "infoc/core/defines.h"

bool string_starts_with(const char* str, const char* beg);

// Returns a darray
char** string_split(char* str, const char* delim);
