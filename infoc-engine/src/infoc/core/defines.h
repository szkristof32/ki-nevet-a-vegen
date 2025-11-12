#pragma once

#include <stdio.h>
#include <stdint.h>

typedef uint8_t bool;
#define true 1
#define false 0

#ifdef IC_DEBUG
#define IC_DEBUGMALLOC
#endif

#ifdef IC_DEBUGMALLOC
#define _STDBOOL
#include "debugmalloc.h"
#endif

/*
* Logs the provided message to the standard error output
*/
#define log_error(...) do { fprintf(stderr, ##__VA_ARGS__); fprintf(stderr, "\n"); } while (false)
/*
* When `err` is true logs the provided error message and returns
*/
#define check_error(err, ...) if (err) { log_error(__VA_ARGS__); return false; }
/*
* When `err` is true logs the provided error message
*/
#define check_error_no_return(err, ...) if (err) { log_error(__VA_ARGS__); }

/*
* Converts bytes to kilobytes (ISO kibibytes)
*/
#define kilobytes(x)	(x*1024)
/*
* Converts bytes to megabytes (ISO mebibytes)
*/
#define megabytes(x)	(kilobytes(x)*1024)
/*
* Converts bytes to gigabytes (ISO gibibytes)
*/
#define gigabytes(x)	(megabytes(x)*1024)

/*
* Gets the length of an array
*
* @warning Only works when `arr` is an array and not a pointer
*/
#define countof(arr)	(sizeof(arr)/sizeof(arr[0]))

#define _typeof(x) __typeof__(x)

#undef bool
