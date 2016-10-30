#include "stdafx.h"

#ifndef LINES_GAMEFIELD_H
#define LINES_GAMEFIELD_H

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
    Cell *selectedCell = nullptr;
};

void addBalls(GameField &gameField);
bool wasLineFoundAndRemoved(GameField &gameField, Cell *cell);
void selectBall(GameField &gameField, Cell *cell);
void moveBall(GameField &gameField, Cell *cell);
Cell &getCellByPos(GameField &gameField, float x, float y);
bool doesUserClickedOnField(GameField &gameField, size_t clickX, size_t clickY);

#endif //LINES_GAMEFIELD_H
