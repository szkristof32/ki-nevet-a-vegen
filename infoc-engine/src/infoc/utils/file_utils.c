#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* file_utils_read_file(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		fprintf(stderr, "Failed to open file: %s!\n", path);
		return "";
	}

	fseek(file, 0, SEEK_END);
	size_t length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = (char*)malloc((length + 1) * sizeof(char));
	if (buffer == NULL)
	{
		fprintf(stderr, "Failed to allocate buffer!\n");
		return "";
	}
	memset(buffer, 0, (length + 1) * sizeof(char));
	fread(buffer, sizeof(char), length, file);
	fclose(file);

	return buffer;
}
