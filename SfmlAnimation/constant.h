#ifndef SFMLANIMATION_CONSTANT_H
#define SFMLANIMATION_CONSTANT_H

using namespace std;
using namespace sf;

const unsigned ANTIALIASING_LEVEL = 8;
const unsigned SCREEN_WIDTH = 540;
const unsigned SCREEN_HEIGHT = 600;

const string WINDOW_TITLE = "SFML Animation";

const unsigned RECTANGLE_COUNT = 8;
const unsigned RECTANGLE_WIDTH = 50;
const unsigned RECTANGLE_HEIGHT = 50;

const unsigned START_LEFT_OFFSET = 0;
const unsigned START_TOP_OFFSET = 10;

const unsigned RECTANGLE_DISTANCE = 10;

const float SPEED_X = 0.2;
const float SPEED_Y = 0.05;
const float SPEED_COLOR = 1;
const float SPEED_SIZE = 0.005;
const float SPEED_ROTATION = 0.05;

const Color START_COLOR = Color(0, 0, 100, 255);

extern vector<map<string, float>> ANIMATION_MODES;

#endif //SFMLANIMATION_CONSTANT_H
