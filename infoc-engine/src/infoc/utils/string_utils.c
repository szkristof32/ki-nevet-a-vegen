#include "string_utils.h"

#include "infoc/core/darray.h"

#include <string.h>

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
