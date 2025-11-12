#pragma once

#ifndef min
/*
* Returns the minimum of `a` and `b`
*
* @warning Can produce unexpected side-effects when `a` or `b` is directly manipulated when passed in (eg. `min(a++, b)`)
*/
#define min(a, b) ((a)<(b)?(a):(b))
#endif
#ifndef max
/*
* Returns the maximum of `a` and `b`
*
* @warning Can produce unexpected side-effects when `a` or `b` is directly manipulated when passed in (eg. `max(a++, b)`)
*/
#define max(a, b) ((a)>(b)?(a):(b))
#endif