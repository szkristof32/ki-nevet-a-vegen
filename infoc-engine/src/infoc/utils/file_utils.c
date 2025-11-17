#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

char* file_utils_read_file(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		char msg[64] = "";
		sprintf_s(msg, sizeof(msg), "Failed to open file (%s)", path);
		perror(msg);
		return (char*)malloc(sizeof(char));
	}

	fseek(file, 0, SEEK_END);
	size_t length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = (char*)malloc((length + 1) * sizeof(char));
	if (buffer == NULL)
	{
		log_error("Failed to allocate buffer!");
		return (char*)malloc(sizeof(char));
	}
	memset(buffer, 0, (length + 1) * sizeof(char));
	fread(buffer, sizeof(char), length, file);
	fclose(file);

	return buffer;
}

void file_utils_create_directory(const char* path)
{
#ifdef _WIN32
	CreateDirectoryA(path, NULL);
#else
	mkdir(path, 0700);
#endif
}
