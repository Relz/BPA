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
const float BALL_RADIUS = CELL_SIZE / 2.5;
const float BALL_DIAMETER = BALL_RADIUS * 2;

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

const vector<Color> ballColors =
{
    Color(255, 0, 0),   // Red
    Color(255, 127, 0), // Orange
    Color(255, 255, 0), // Yellow
    Color(0, 255, 0),   // Green
    Color(0, 255, 255), // Cyan
    Color(0, 0, 255),   // Blue
    Color(75, 0, 130)   // Purple
};

#endif //SFMLANIMATION_CONSTANT_H
