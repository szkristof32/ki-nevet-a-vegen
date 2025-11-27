#pragma once

#include "defines.h"

/**
 * Dynamic array header. For private usage.
 * The public data section begins right after the header.
 * All public methods require the data section as input and
 * return with the data section
 */
typedef struct darray_t
{
	/** Element count of the array */
	size_t count;
	/** Total capacity of the array */
	size_t capacity;
	/** Size of one element in bytes */
	size_t element_size;
} darray_t;

/**
 * Private function. Use `darray_create` instead!
 */
void* _darray_create(size_t element_size, size_t initial_capacity);
/**
 * Destroys the darray
 *
 * @param array A pointer to the data section of the darray
 */
void darray_destroy(void* array);

/**
 * Private function. Use `darray_push` instead!
 */
void* _darray_push(void* array, const void* value_ptr);
/**
 * Private function. Use `darray_erase` instead!
 */
void* _darray_erase(void* array, size_t index);
/**
 * Private function. Only for internal use.
 */
void* _darray_resize(void* array, size_t new_count);

/**
 * Determines the length of the darray
 *
 * @param array A pointer to the data section of the darray
 *
 * @returns The array's length
 */
size_t darray_count(void* array);

#define DARRAY_INITIAL_CAPACITY 2
/**
* Creates a darray with an initial capacity of 2
*
* @param type The type of the elements the darray should hold
*
* @returns The data section of the darray
*/
#define darray_create(type) (type*)_darray_create(sizeof(type), DARRAY_INITIAL_CAPACITY)
/**
 * Creates a darray with the provided inital capacity
 *
 * @param type The type of the elements the darray should hold
 * @param capacity The initial capacity of the array
 *
 * @returns The data section of the darray
 */
#define darray_reserve(type, capacity) _darray_create(sizeof(type), capacity)
/**
 * Pushes an element into the array
 *
 * @param array A pointer to the data section of the array (`array` must be an lvalue)
 * @param value The element to be pushed into the array
 *
 * @warning The method can change the location of `array` in the memory
 */
#define darray_push(array, value) { _typeof(value) temp = value; array = _darray_push(array, &temp); }
/**
 * Removes an element from the array
 * 
 * @param array A pointer to the data section of the array (`array= must be an lvalue)
 * @param index The index of the element o be removed
 * 
 * @warning The method can change the location of `array` in the memory
 */
#define darray_erase(array, index) { array = _darray_erase(array, index); }

/**
 * Removes all the elements from the array
 * 
 * @param array The array to be cleared
 */
void darray_clear(void* array);
