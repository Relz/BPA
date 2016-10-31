#include "stdafx.h"

#ifndef LINES_GAMEVIEW_H
#define LINES_GAMEVIEW_H

struct BallPointerOnField
{
    CircleShape *ball;
    PositionOnField pos;
};

struct Cell
{
    RectangleShape shape;
    CircleShape *ball;
    PositionOnField pos;
};

struct GameField
{
    float x;
    float y;
    Cell cells[CELL_COUNT];
    size_t ballCount = 0;
    size_t score = 0;
    Cell *selectedCell = nullptr;
    BallPointerOnField futureBallsPositions[BALLS_PER_COUP];
};

struct GameTopBar
{
    Text ballCountText;
    Text ballCountNum;
    Text scoreText;
    Text scoreNum;
    Font font;
    CircleShape futureBalls[BALLS_PER_COUP];
};

struct GameView
{
    GameTopBar gameTopBar;
    GameField gameField;
};

#endif //LINES_GAMEVIEW_H
