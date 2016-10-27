#include "constant.h"

vector<map<string, map<string, float>>> ANIMATION_MODES =
        {
                {
                        {"SPEED", {{"X", SPEED_X}, {"Y", 0}}},
                        {"WIDTH", {{"TO", RECTANGLE_WIDTH}}},
                        {"HEIGHT", {{"TO", RECTANGLE_HEIGHT}}},
                        {"COLOR_RED", {{"TO", 0}}},
                        {"COLOR_GREEN", {{"TO", 0}}},
                        {"COLOR_BLUE", {{"TO", 100}}},
                        {"OPACITY", {{"TO", 255}}},
                        {"ROTATION", {{"TO", 0}}}
                },
                {
                        {"SPEED", {{"X", 0}, {"Y", SPEED_Y}}},
                        {"WIDTH", {{"TO", RECTANGLE_WIDTH}}},
                        {"HEIGHT", {{"TO", RECTANGLE_HEIGHT}}},
                        {"COLOR_RED", {{"TO", 0}}},
                        {"COLOR_GREEN", {{"TO", 100}}},
                        {"COLOR_BLUE", {{"TO", 0}}},
                        {"OPACITY", {{"TO", 255}}},
                        {"ROTATION", {{"TO", 0}}}
                },
                {
                        {"SPEED", {{"X", -SPEED_X}, {"Y", -SPEED_Y}}},
                        {"WIDTH", {{"TO", RECTANGLE_WIDTH}}},
                        {"HEIGHT", {{"TO", RECTANGLE_HEIGHT}}},
                        {"COLOR_RED", {{"TO", 0}}},
                        {"COLOR_GREEN", {{"TO", 100}}},
                        {"COLOR_BLUE", {{"TO", 0}}},
                        {"OPACITY", {{"TO", 100}}},
                        {"ROTATION", {{"TO", 0}}}
                },
                {
                        {"SPEED", {{"X", SPEED_X}, {"Y", 0}}},
                        {"WIDTH", {{"TO", RECTANGLE_WIDTH}}},
                        {"HEIGHT", {{"TO", RECTANGLE_HEIGHT / 2}}},
                        {"COLOR_RED", {{"TO", 200}}},
                        {"COLOR_GREEN", {{"TO", 0}}},
                        {"COLOR_BLUE", {{"TO", 0}}},
                        {"OPACITY", {{"TO", 100}}},
                        {"ROTATION", {{"TO", 0}}}
                },
                {
                        {"SPEED", {{"X", 0}, {"Y", SPEED_Y}}},
                        {"WIDTH", {{"TO", RECTANGLE_WIDTH / 5}}},
                        {"HEIGHT", {{"TO", RECTANGLE_HEIGHT}}},
                        {"COLOR_RED", {{"TO", 0}}},
                        {"COLOR_GREEN", {{"TO", 100}}},
                        {"COLOR_BLUE", {{"TO", 200}}},
                        {"OPACITY", {{"TO", 255}}},
                        {"ROTATION", {{"TO", 0}}}
                },
                {
                        {"SPEED", {{"X", -SPEED_X}, {"Y", -SPEED_Y}}},
                        {"WIDTH", {{"TO", RECTANGLE_WIDTH}}},
                        {"HEIGHT", {{"TO", RECTANGLE_HEIGHT}}},
                        {"COLOR_RED", {{"TO", 100}}},
                        {"COLOR_GREEN", {{"TO", 0}}},
                        {"COLOR_BLUE", {{"TO", 20}}},
                        {"OPACITY", {{"TO", 200}}},
                        {"ROTATION", {{"TO", 0}}}
                },
                {
                        {"SPEED", {{"X", 0}, {"Y", 0}}},
                        {"WIDTH", {{"TO", RECTANGLE_WIDTH}}},
                        {"HEIGHT", {{"TO", RECTANGLE_HEIGHT}}},
                        {"COLOR_RED", {{"TO", 100}}},
                        {"COLOR_GREEN", {{"TO", 0}}},
                        {"COLOR_BLUE", {{"TO", 20}}},
                        {"OPACITY", {{"TO", 200}}},
                        {"ROTATION", {{"TO", 90}}}
                }
        };