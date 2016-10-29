#include "initialize.h"

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
        gameField.cells[cellPos].ball->setFillColor(ballColors[randomTool.getRandomValue(0, ballColors.size() - 1)]);
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