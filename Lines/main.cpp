#include <iostream>
#include "stdafx.h"
#include "constant.h"
#include "gameField.h"


// Инициализация игровых ячеек
void initCells(GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_Y; ++i)
    {
        for (size_t j = 0; j < CELL_COUNT_X; ++j)
        {
            gameField.cells[i * CELL_COUNT_Y + j].shape.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
            gameField.cells[i * CELL_COUNT_Y + j].shape.setOutlineThickness(CELL_OUTLINE_THICKNESS);
            gameField.cells[i * CELL_COUNT_Y + j].shape.setOutlineColor(CELL_OUTLINE_COLOR);
            gameField.cells[i * CELL_COUNT_Y + j].shape.setPosition(j * CELL_SIZE + gameField.x, i * CELL_SIZE + gameField.y);
            gameField.cells[i * CELL_COUNT_Y + j].ball = nullptr;
        }
    }
}

// Инициализация игрового поля
void initGameField(GameField &gameField, Vector2f &windowCenter)
{
    gameField.x = windowCenter.x - CELL_COUNT_X * CELL_SIZE / 2;
    gameField.y = windowCenter.y - CELL_COUNT_Y * CELL_SIZE / 2
    initCells(gameField);
}

// Отрисовка игрового поля
void drawGameField(RenderWindow &window, GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_X * CELL_COUNT_Y; ++i)
    {
        window.draw(gameField.cells[i].shape);
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

// Обработка событий на форме
void handleEvents(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed:
            {
                window.close();
                break;
            }
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << event.mouseButton.x << "\n";
                    cout << event.mouseButton.y << "\n";
                }
                break;
            }
        }
    }
}

// Игровой цикл
void gameLoop(RenderWindow &window, GameField &gameField)
{
    while (window.isOpen())
    {
        handleEvents(window);
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