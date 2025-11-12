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

#define log_error(...) do { fprintf(stderr, ##__VA_ARGS__); fprintf(stderr, "\n"); } while (false)
#define check_error(err, ...) if (err) { log_error(__VA_ARGS__); return false; }
#define check_error_no_return(err, ...) if (err) { log_error(__VA_ARGS__); }

#define kilobytes(x)	(x*1024)
#define megabytes(x)	(kilobytes(x)*1024)
#define gigabytes(x)	(megabytes(x)*1024)

#define countof(arr)	(sizeof(arr)/sizeof(arr[0]))

#ifndef min
#define min(a, b) ((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a, b) ((a)>(b)?(a):(b))
#endif

#define _typeof(x) __typeof__(x)

#undef bool
