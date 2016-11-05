#ifndef SFMLANIMATION_CONSTANT_H
#define SFMLANIMATION_CONSTANT_H

#include "stdafx.h"

const unsigned ANTIALIASING_LEVEL = 8;
const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;

const string WINDOW_TITLE = "Lines";

const size_t CELL_COUNT_X = 9;
const size_t CELL_COUNT_Y = 9;
const size_t CELL_COUNT = CELL_COUNT_X * CELL_COUNT_Y;
const float CELL_SIZE = 50;
const Color CELL_FILL_COLOR = Color(192, 192, 192);
const float CELL_OUTLINE_THICKNESS = 2;
const Color CELL_OUTLINE_COLOR = Color(63, 63, 63);

const size_t BALLS_PER_COUP = 3;
const size_t LINE_BALL_COUNT = 5;
const float BALL_RADIUS = CELL_SIZE / 2.5;
const float BALL_DIAMETER = BALL_RADIUS * 2;
const float FUTURE_BALL_RADIUS = BALL_RADIUS / 2;
const float FUTURE_BALL_DIAMETER = FUTURE_BALL_RADIUS * 2;
const float BALL_MOVEMENT_SPEED = 0.8;

const float TOPBAR_FUTURE_BALLS_LEFT_PADDING = 20;
const float TOPBAR_FUTURE_BALLS_MAX_COUNT = 3;

const string TEXT_BALLS = "BALLS ";
const string TEXT_SCORE = "SCORE ";

const Color GAME_OVER_BACKGROUND_COLOR = Color(255, 255, 255, 200);
const string TEXT_GAME_OVER = "Game Over";
const string TEXT_GAME_OVER_SCORE = "Score: ";
const string TEXT_GAME_OVER_RESTART_BUTTON = "Restart";
const Color GAME_OVER_RESTART_BUTTON_TEXT_OUTLINE_COLOR = Color::Black;
const Color GAME_OVER_RESTART_BUTTON_FILL_COLOR = Color(0, 100, 0);

struct PositionOnField
{
    size_t x;
    size_t y;

    PositionOnField(size_t x = 0, size_t y = 0)
    {
        PositionOnField::x = x;
        PositionOnField::y = y;
    }
};

const vector<Color> ballColors =
{
    Color(100, 0, 0),   // Red
    Color(200, 0, 0),   // Orange
    Color(165, 165, 45),// Yellow
    Color(40, 169, 30), // Green
    Color(10, 150, 180),// Cyan
    Color(30, 40, 150), // Blue
    Color(180, 50, 180) // Purple
};

#endif //SFMLANIMATION_CONSTANT_H
