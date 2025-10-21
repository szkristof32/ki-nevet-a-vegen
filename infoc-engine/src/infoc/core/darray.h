#pragma once

#include "defines.h"

typedef struct darray_t
{
	size_t count;
	size_t capacity;
	size_t element_size;
} darray_t;

void* _darray_create(size_t element_size, size_t initial_capacity);
void darray_destroy(void* array);

void* _darray_push(void* array, const void* value_ptr);
void* _darray_resize(void* array, size_t new_count);

size_t darray_count(void* array);

#define DARRAY_INITIAL_CAPACITY 2
#define darray_create(type) (type*)_darray_create(sizeof(type), DARRAY_INITIAL_CAPACITY)
#define darray_reserve(type, capacity) _darray_create(sizeof(type), capacity)
#define darray_push(array, value) { void* temp = &(value); array = _darray_push(array, temp); }
