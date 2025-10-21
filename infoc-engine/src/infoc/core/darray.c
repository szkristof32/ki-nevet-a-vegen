#include "darray.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DARRAY_RESIZE_AMOUNT 1.5f

void* _darray_create(size_t element_size, size_t initial_capacity)
{
	size_t header_size = sizeof(darray_t);
	size_t array_size = element_size * initial_capacity;

	void* array = malloc(header_size + array_size);
	if (array == NULL)
	{
		fprintf(stderr, "Failed to allocate darray!\n");
		return false;
	}

	memset(array, 0, header_size + array_size);

	darray_t* header = array;
	header->element_size = element_size;
	header->count = 0;
	header->capacity = initial_capacity;

	return (uint8_t*)array + header_size;
}

void darray_destroy(void* array)
{
	size_t header_size = sizeof(darray_t);
	darray_t* header = (darray_t*)((uint8_t*)array - header_size);

	free(header);
}

void* _darray_push(void* array, const void* value_ptr)
{
	size_t header_size = sizeof(darray_t);
	darray_t* header = (darray_t*)((uint8_t*)array - header_size);

	if (header->count >= header->capacity)
	{
		array = _darray_resize(array, (size_t)ceil(header->capacity * DARRAY_RESIZE_AMOUNT));
		header = (darray_t*)((uint8_t*)array - header_size);
	}

	memcpy((uint8_t*)array + (header->count * header->element_size), value_ptr, header->element_size);
	header->count++;

	return array;
}

void* _darray_resize(void* array, size_t new_count)
{
	size_t header_size = sizeof(darray_t);
	darray_t* header = (darray_t*)((uint8_t*)array - header_size);

	void* temp = _darray_create(header->element_size, new_count);
	darray_t* new_header = (darray_t*)((uint8_t*)temp - header_size);
	new_header->count = header->count;

	memcpy(temp, array, header->count * header->element_size);
	darray_destroy(array);

	return temp;
}

size_t darray_count(void* array)
{
	size_t header_size = sizeof(darray_t);
	darray_t* header = (darray_t*)((uint8_t*)array - header_size);

	return header->count;
}
