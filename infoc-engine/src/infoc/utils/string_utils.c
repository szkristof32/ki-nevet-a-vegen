#include "string_utils.h"

#include "infoc/core/darray.h"

#include <string.h>

#if _WIN32
#include <Windows.h>
#endif

bool string_starts_with(const char* str, const char* beg)
{
	return strncmp(str, beg, strlen(beg)) == 0;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#endif

char** string_split(char* str, const char* delim)
{
	char** tokens = darray_create(char*);

	// TODO: fix strtok
	char* token = strtok(str, delim);

	while (token != NULL)
	{
		darray_push(tokens, token);
		token = strtok(NULL, delim);
	}

	return tokens;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

wchar_t* string_to_wstring(const char* str)
{
	size_t length = strlen(str);
#if _WIN32
	int32_t allocation_size = MultiByteToWideChar(CP_UTF8, 0, str, length, NULL, 0);
	wchar_t* wide_string = (wchar_t*)malloc((allocation_size + 1) * sizeof(wchar_t));
	if (!wide_string)
		return NULL;

	MultiByteToWideChar(CP_UTF8, 0, str, length, wide_string, allocation_size);
	wide_string[allocation_size] = 0;

	return wide_string;
#endif
}
