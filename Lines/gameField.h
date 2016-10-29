#include "stdafx.h"
#include "constant.h"

#ifndef LINES_GAMEFIELD_H
#define LINES_GAMEFIELD_H

struct Cell
{
    RectangleShape shape;
    size_t posX;
    size_t posY;
    CircleShape ball;
    bool isEmpty = true;
};

struct GameField
{
    float x;
    float y;
    Cell cells[CELL_COUNT_X * CELL_COUNT_Y];
    size_t ballCount = START_BALL_COUNT;
};

#endif //LINES_GAMEFIELD_H
