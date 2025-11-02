#pragma once

#include <stdio.h>
#include <stdint.h>

typedef uint8_t bool;
#define true 1
#define false 0

#define kilobytes(x)	(x*1024)
#define megabytes(x)	(kilobytes(x)*1024)
#define gigabytes(x)	(megabytes(x)*1024)

#define countof(arr)	(sizeof(arr)/sizeof(arr[0]))

#ifdef _MSC_VER
	#define _typeof(x) __typeof__(x)
#else
	#define _typeof(x) typeof(x)
#endif
