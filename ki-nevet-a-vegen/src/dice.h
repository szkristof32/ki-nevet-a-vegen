#pragma once

#include "infoc/core/defines.h"

/**
 * Dice
 */
typedef struct dice_t
{
	/** Dice side count */
	uint32_t sides;
	/** Number of dices */
	uint32_t dice_count;
} dice_t;

/**
 * Generates a random number according to the dice configuration.
 * Example: 2d6: generates two numbers between 1 and 6 and returns the sum.
 *
 * @param dice The dice configuration
 *
 * @returns The rolled value
 */
uint32_t dice_roll(const dice_t* dice);
