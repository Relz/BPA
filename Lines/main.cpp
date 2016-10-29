#include "stdafx.h"
#include "constant.h"
#include "gameField.h"
#include "randomTool.h"
#include "handleEvents.h"

// Получение случайных координат игрового поля, на которых нет шара
void getRandomEmptyFieldPosition(GameField &gameField, RandomTool &randomTool, FieldPosition &fieldPosition)
{
    do
    {
        fieldPosition.x = randomTool.getRandomValue(0, CELL_COUNT_X - 1);
        fieldPosition.y = randomTool.getRandomValue(0, CELL_COUNT_Y - 1);
    } while (!gameField.cells[fieldPosition.y * CELL_COUNT_X + fieldPosition.x].isEmpty);
}

// Инициализация начальных шаров
void initStartBalls(GameField &gameField)
{
    RandomTool randomTool;
    for (size_t i = 0; i < START_BALL_COUNT; ++i)
    {
        FieldPosition fieldPosition;
        getRandomEmptyFieldPosition(gameField, randomTool, fieldPosition);
        size_t cellPos = fieldPosition.y * CELL_COUNT_X + fieldPosition.x;

        gameField.cells[cellPos].ball = new CircleShape;
        gameField.cells[cellPos].ball->setPosition(fieldPosition.x * CELL_SIZE + gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                                                  fieldPosition.y * CELL_SIZE + gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
        gameField.cells[cellPos].ball->setRadius(BALL_RADIUS);
        gameField.cells[cellPos].ball->setFillColor(Color(0, 100, 0));
        gameField.cells[cellPos].isEmpty = false;
    }
}

// Инициализация игровых ячеек
void initCells(GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_Y; ++i)
    {
        for (size_t j = 0; j < CELL_COUNT_X; ++j)
        {
            size_t cellPos = i * CELL_COUNT_X + j;
            gameField.cells[cellPos].shape.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
            gameField.cells[cellPos].shape.setOutlineThickness(CELL_OUTLINE_THICKNESS);
            gameField.cells[cellPos].shape.setOutlineColor(CELL_OUTLINE_COLOR);
            gameField.cells[cellPos].shape.setPosition(j * CELL_SIZE + gameField.x, i * CELL_SIZE + gameField.y);
            gameField.cells[cellPos].posX = j;
            gameField.cells[cellPos].posY = i;
            gameField.cells[cellPos].ball = nullptr;
        }
    }
}

// Инициализация игрового поля
void initGameField(GameField &gameField, Vector2f &windowCenter)
{
    gameField.x = windowCenter.x - CELL_COUNT_X * CELL_SIZE / 2;
    gameField.y = windowCenter.y - CELL_COUNT_Y * CELL_SIZE / 2;
    initCells(gameField);
    initStartBalls(gameField);
}

// Отрисовка игрового поля
void drawGameField(RenderWindow &window, GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_X * CELL_COUNT_Y; ++i)
    {
        window.draw(gameField.cells[i].shape);
        if (gameField.cells[i].ball != nullptr)
        {
            window.draw(*(gameField.cells[i].ball));
        }
    }
}

// Отрисовка объектов на форме
void drawObjects(RenderWindow &window, GameField &gameField)
{
    drawGameField(window, gameField);
    window.display();
}

// Обновление Формы
void update(RenderWindow &window, GameField &gameField)
{
    drawObjects(window, gameField);
    window.clear(Color::White);
}

// Игровой цикл
void gameLoop(RenderWindow &window, GameField &gameField)
{
    while (window.isOpen())
    {
        handleEvents(window, gameField);
        update(window, gameField);
    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE, Style::Close, settings);
    Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    GameField gameField;
    initGameField(gameField, windowCenter);

    gameLoop(window, gameField);

    return 0;
}