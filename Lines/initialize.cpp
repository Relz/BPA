#include "initialize.h"

// Инициализация игровых ячеек
void initCells(GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_Y; ++i)
    {
        for (size_t j = 0; j < CELL_COUNT_X; ++j)
        {
            size_t cellPos = i * CELL_COUNT_X + j;
            gameField.cells[cellPos].shape.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
            gameField.cells[cellPos].shape.setFillColor(CELL_FILL_COLOR);
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
}