#include "file_utils.h"

#include "infoc/core/darray.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <dirent.h>
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

bool file_utils_file_exists(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file)
	{
		fclose(file);
		return true;
	}

	return false;
}

void file_utils_create_directory(const char* path)
{
#ifdef _WIN32
	CreateDirectoryA(path, NULL);
#else
	mkdir(path, 0700);
#endif
}

char** file_utils_get_files_in_directory(const char* path)
{
	size_t path_length = strlen(path);
	char** files = NULL;

#ifdef _WIN32
	char* folder = (char*)malloc((path_length + 7) * sizeof(char));
	if (!folder)
		return NULL;
	sprintf_s(folder, path_length + 7, "%s/*.dat", path);

	WIN32_FIND_DATAA file_data;
	HANDLE find = FindFirstFileA(folder, &file_data);
	if (find == INVALID_HANDLE_VALUE)
	{
		free(folder);
		return NULL;
	}

	files = darray_create(char*);

	do
	{
		if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;
		char* file = (char*)malloc(sizeof(file_data.cFileName));
		memcpy(file, file_data.cFileName, sizeof(file_data.cFileName));
		darray_push(files, file);
	} while (FindNextFileA(find, &file_data));

	FindClose(find);

	free(folder);
#else
	DIR* directory = opendir(path);
	struct dirent* entry = NULL;

	files = darray_create(char*);

	while ((entry = readdir(directory)) != NULL)
	{
		darray_push(files, entry->d_name);
	}

	closedir(directory);
#endif

	return files;
}
