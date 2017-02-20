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
static const std::string TMX_ENVIRONMENT_TYPE = "Окружение";
static const std::string TMX_PLAYER_NAME = "Игрок";
static const std::string TMX_COLLISION_BLOCK_TYPE = "Блок коллизии";
static const std::string TMX_COIN_TYPE = "Монета";
static const std::string TMX_ENEMY_TYPE = "Противник";
static const std::string TMX_BELOVED_NAME = "Любимая";
static const std::string TMX_VILLAIN_NAME = "Злодей";
static const std::string TMX_VILLAIN_SPIRIT_NAME = "Дух злодея";
static const std::string TMX_DEAD_LINE_TYPE = "Линия смерти";
static const std::string TMX_ACTION_LINE_TYPE = "Линия события";

static const std::string TMX_MAP_LEFT_BORDER = "Левая граница карты";
static const std::string TMX_MAP_RIGHT_BORDER = "Правая граница карты";

static const std::string TMX_ACTION_GAME_BEGINNING = "Начало игры";
static const std::string TMX_ACTION_BELOVED_FOUND= "Нахождение любимой";
static const std::string TMX_ACTION_VILLAIN_APPEARING = "Появление злодея";
static const std::string ACTION_VILLAIN_APPEARED = "Злодей появился";
static const std::string ACTION_FIRE_VILLAIN_DISAPPEARING = "Исчезновение злодея";

static const std::string SKILL_SPIRIT = "Spirit";
static const std::string SKILL_CLOUDSTRIKE = "Cloudstrike";
static const std::string SKILL_SHIELD = "Shield";

#endif //ULTIMATE_SHAMAN_KING_CONSTANT_H
