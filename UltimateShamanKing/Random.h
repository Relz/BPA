#ifndef ULTIMATE_SHAMAN_KING_RANDOM_H
#define ULTIMATE_SHAMAN_KING_RANDOM_H

#include "stdafx.h"

struct Random
{
	std::random_device randomDevice;
	std::mt19937 gen;

	size_t GetRandomValue(size_t min, size_t max)
	{
		gen.seed(randomDevice());
		std::uniform_int_distribution<size_t> dist(min, max);
		return dist(gen);
	}
};

static Random myRandom;

#endif //ULTIMATE_SHAMAN_KING_RANDOM_H
