#include "stdafx.h"

#ifndef LINES_GAMEVIEW_H
#define LINES_GAMEVIEW_H

struct Cell
{
    RectangleShape shape;
    size_t posX;
    size_t posY;
    CircleShape *ball;
};

struct GameField
{
    float x;
    float y;
    Cell cells[CELL_COUNT];
    size_t ballCount = 0;
    size_t score = 0;
    Cell *selectedCell = nullptr;
};

struct GameTopBar
{
    Text ballCountText;
    Text ballCountNum;
    Text scoreText;
    Text scoreNum;
    Font font;
};

struct GameView
{
    GameTopBar gameTopBar;
    GameField gameField;
};

#endif //LINES_GAMEVIEW_H
