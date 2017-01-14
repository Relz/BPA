#ifndef ULTIMATE_SHAMAN_KING_CONSTANT_H
#define ULTIMATE_SHAMAN_KING_CONSTANT_H

const unsigned ANTIALIASING_LEVEL = 8;
const sf::Vector2u SCREEN_SIZE(1280, 640);
const sf::Color BACKGROUND_COLOR = sf::Color(200, 200, 255);

const float PLAYER_SPEED_X = 7;
const float PLAYER_SPEED_UP = 4;
const float PLAYER_SPEED_DOWN = 2;
const float GRAVITY = 0.2;

const std::string WINDOW_TITLE = "Ultimate Shaman King";

const std::string TMX_PATH = "../res/level0.tmx";
const std::string TMX_TILES = "Тайлы";
const std::string TMX_ENVIRONMENT = "Окружение";
const std::string TMX_PLAYER = "Игрок";
const std::string TMX_COLLISION_BLOCK = "Блок коллизии";
const std::string TMX_COIN = "coin";
const std::string TMX_ENEMIES = "enemies";

#endif //ULTIMATE_SHAMAN_KING_CONSTANT_H
