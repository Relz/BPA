#include "constant.h"

vector<map<string, float>> ANIMATION_MODES =
        {
                {
                        {"SPEED_X", SPEED_X},
                        {"SPEED_Y", 0},
                        {"WIDTH", RECTANGLE_WIDTH},
                        {"HEIGHT", RECTANGLE_HEIGHT},
                        {"COLOR_RED", 0},
                        {"COLOR_GREEN", 0},
                        {"COLOR_BLUE", 100},
                        {"OPACITY", 255},
                        {"ROTATION", 0}
                },
                {
                        {"SPEED_X", 0},
                        {"SPEED_Y", SPEED_Y},
                        {"WIDTH", RECTANGLE_WIDTH},
                        {"HEIGHT", RECTANGLE_HEIGHT},
                        {"COLOR_RED", 0},
                        {"COLOR_GREEN", 100},
                        {"COLOR_BLUE", 0},
                        {"OPACITY", 255},
                        {"ROTATION", 0}
                },
                {
                        {"SPEED_X", -SPEED_X},
                        {"SPEED_Y", -SPEED_Y},
                        {"WIDTH", RECTANGLE_WIDTH},
                        {"HEIGHT", RECTANGLE_HEIGHT},
                        {"COLOR_RED", 0},
                        {"COLOR_GREEN", 100},
                        {"COLOR_BLUE", 0},
                        {"OPACITY", 100},
                        {"ROTATION", 0}
                },
                {
                        {"SPEED_X", SPEED_X},
                        {"SPEED_Y", 0},
                        {"WIDTH", RECTANGLE_WIDTH},
                        {"HEIGHT", RECTANGLE_HEIGHT / 2},
                        {"COLOR_RED", 200},
                        {"COLOR_GREEN", 0},
                        {"COLOR_BLUE", 0},
                        {"OPACITY", 100},
                        {"ROTATION", 0}
                },
                {
                        {"SPEED_X", 0},
                        {"SPEED_Y", SPEED_Y},
                        {"WIDTH", RECTANGLE_WIDTH / 5},
                        {"HEIGHT", RECTANGLE_HEIGHT},
                        {"COLOR_RED", 0},
                        {"COLOR_GREEN", 100},
                        {"COLOR_BLUE", 200},
                        {"OPACITY", 255},
                        {"ROTATION", 0}
                },
                {
                        {"SPEED_X", -SPEED_X},
                        {"SPEED_Y", -SPEED_Y},
                        {"WIDTH", RECTANGLE_WIDTH},
                        {"HEIGHT", RECTANGLE_HEIGHT},
                        {"COLOR_RED", 100},
                        {"COLOR_GREEN", 0},
                        {"COLOR_BLUE", 20},
                        {"OPACITY", 200},
                        {"ROTATION", 0}
                },
                {
                        {"SPEED_X", 0},
                        {"SPEED_Y", 0},
                        {"WIDTH", RECTANGLE_WIDTH},
                        {"HEIGHT", RECTANGLE_HEIGHT},
                        {"COLOR_RED", 100},
                        {"COLOR_GREEN", 0},
                        {"COLOR_BLUE", 20},
                        {"OPACITY", 200},
                        {"ROTATION", 90}
                }
        };