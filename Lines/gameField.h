#include "stdafx.h"

#ifndef LINES_GAMEFIELD_H
#define LINES_GAMEFIELD_H

void setRandomFutureBalls(GameView &gameView);
void addBalls(GameView &gameView);
bool wasLineFoundAndRemoved(GameField &gameField, Cell *cell);
void selectBall(GameField &gameField, Cell *cell);
void moveBall(GameField &gameField, Cell *cell);
Cell &getCellByPos(GameField &gameField, float x, float y);
bool doesUserClickedOnField(GameField &gameField, size_t clickX, size_t clickY);

#endif //LINES_GAMEFIELD_H
