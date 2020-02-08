#include "stdafx.h"

#ifndef LINES_GAMEFIELD_H
#define LINES_GAMEFIELD_H

void setRandomFutureBalls(GameView &gameView);
void addBalls(GameView &gameView);
void selectBall(GameField &gameField, Cell *cell);
void initMoves(GameField &gameField, Cell *cell);
void moveBall(GameView &gameView);
Cell &getCellByPos(GameField &gameField, float x, float y);
void clearGameField(GameField &gameField);
void removeFreePositionOnGameField(vector<PositionOnField> &freePositionsOnField, PositionOnField positionOnField);

#endif //LINES_GAMEFIELD_H
