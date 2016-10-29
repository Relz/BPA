#include "stdafx.h"

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