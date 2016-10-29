#ifndef SFMLANIMATION_CONSTANT_H
#define SFMLANIMATION_CONSTANT_H

#include "stdafx.h"

const unsigned ANTIALIASING_LEVEL = 8;
const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;

const string WINDOW_TITLE = "Lines";

const size_t CELL_COUNT_X = 9;
const size_t CELL_COUNT_Y = 9;
const float CELL_SIZE = 50;
const Color CELL_FILL_COLOR = Color(255, 255, 255);
const Color CELL_OUTLINE_COLOR = Color(0, 0, 0);
const float CELL_OUTLINE_THICKNESS = 2;

const size_t START_BALL_COUNT = 3;
const float BALL_SIZE = CELL_SIZE / 2.5;

struct FieldPosition
{
    size_t x;
    size_t y;

    FieldPosition(size_t x = 0, size_t y = 0)
    {
        FieldPosition::x = x;
        FieldPosition::y = y;
    }
};

#endif //SFMLANIMATION_CONSTANT_H
