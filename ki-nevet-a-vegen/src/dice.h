#pragma once

#include "infoc/core/defines.h"

typedef struct dice_t
{
	uint32_t sides;
	uint32_t dice_count;
} dice_t;

uint32_t dice_roll(const dice_t* dice);
