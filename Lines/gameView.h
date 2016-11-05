#include "stdafx.h"

#ifndef LINES_GAMEVIEW_H
#define LINES_GAMEVIEW_H

struct BallPointerOnField
{
    CircleShape *ball = nullptr;
    PositionOnField pos;
};

struct Cell
{
    RectangleShape shape;
    CircleShape *ball = nullptr;
    PositionOnField pos;
    size_t distance = 0;
};

struct GameInfo
{
    size_t ballCount = 0;
    size_t score = 0;
};

struct GameField
{
    float x;
    float y;
    Cell cells[CELL_COUNT];
    Cell *selectedCell = nullptr;
    BallPointerOnField futureBallsPositions[BALLS_PER_COUP];
    vector<PositionOnField> moves;
    vector<PositionOnField> freePositionsOnField;
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

struct Button
{
    RectangleShape shape;
    Text text;
};

struct GameBottomBar
{
    Font font;
    Button restartButton;
};

struct GameOverView
{
    RectangleShape background;
    Font font;
    Text gameOverText;
    Text scoreText;
    Button restartButton;
};

struct GameView
{
    Vector2f windowCenter;
    GameTopBar gameTopBar;
    GameField gameField;
    GameBottomBar gameBottomBar;
    GameInfo gameInfo;
    GameOverView gameOverView;
    bool isGameOver = false;
};

bool doesUserClickedOnRestartButton(Button &restartButton, size_t clickX, size_t clickY);
bool doesUserClickedOnRestartButtonOnGameOverView(Button &restartButton, size_t clickX, size_t clickY);
bool doesUserClickedOnField(GameField &gameField, size_t clickX, size_t clickY);
void restartGame(GameView &gameView);

#endif //LINES_GAMEVIEW_H
