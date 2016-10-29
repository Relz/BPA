#ifndef LINES_RANDOMTOOL_H
#define LINES_RANDOMTOOL_H

#include "stdafx.h"

struct RandomTool
{
    random_device randomDevice;
    mt19937 gen;

    size_t getRandomValue(size_t min, size_t max)
    {
        gen.seed(randomDevice());
        uniform_int_distribution<size_t> dist(min, max);
        return dist(gen);
    }
};

#endif //LINES_RANDOMTOOL_H
