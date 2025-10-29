#include "dice.h"

#include <stdlib.h>
#include <time.h>

static bool s_initialised = false;

static void _init()
{
	if (s_initialised)
		return;

	srand((uint32_t)time(NULL));
	s_initialised = true;
}

uint32_t dice_roll(const dice_t* dice)
{
	_init();

	uint32_t total = 0;
	for (uint32_t i = 0; i < dice->dice_count; i++)
	{
		total += (rand() % dice->sides) + 1;
	}

	return total;
}
