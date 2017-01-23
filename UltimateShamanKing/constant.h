#ifndef ULTIMATE_SHAMAN_KING_CONSTANT_H
#define ULTIMATE_SHAMAN_KING_CONSTANT_H

static const unsigned ANTIALIASING_LEVEL = 8;
static const sf::Vector2u SCREEN_SIZE(1280, 640);
static const sf::Color BACKGROUND_COLOR = sf::Color(200, 200, 255);
static const float CAMERA_ZOOM = 2.0f;

static const float PLAYER_SPEED_X = 7;
static const float PLAYER_SPEED_UP = 4;
static const float PLAYER_SPEED_DOWN = 2;
static const float GRAVITY = 0.2;

static const float MONSTER_SPEED_X = 7;
static const float MONSTER_SPEED_UP = 4;
static const float MONSTER_SPEED_DOWN = 2;

static const std::string WINDOW_TITLE = "Ultimate Shaman King";

static const std::string TMX_PATH = "../res/level0.tmx";
static const std::string TMX_TILES = "Тайлы";
static const std::string TMX_ENVIRONMENT = "Окружение";
static const std::string TMX_PLAYER = "Игрок";
static const std::string TMX_COLLISION_BLOCK = "Блок коллизии";
static const std::string TMX_COIN = "coin";
static const std::string TMX_ENEMY = "Противник";

static const std::string MAP_LEFT_BORDER = "Левая граница карты";
static const std::string MAP_RIGHT_BORDER = "Правая граница карты";

#endif //ULTIMATE_SHAMAN_KING_CONSTANT_H
