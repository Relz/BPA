#ifndef LINES_INITIALIZE_H
#define LINES_INITIALIZE_H

#include "stdafx.h"

void initGameField(GameField &gameField, Vector2f &windowCenter);
bool initGameTopBar(GameView &gameView);
bool initGameOverView(GameView &gameView);
bool initGameView(RenderWindow &window, GameView &gameView);
void initFreePositionsOnField(vector<PositionOnField> &freePositionsOnField);

#endif //LINES_INITIALIZE_H
