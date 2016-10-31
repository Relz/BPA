#include "stdafx.h"

// Отрисовка верхней панели
void drawGameTopBar(RenderWindow &window, GameTopBar &gameTopBar)
{
    window.draw(gameTopBar.ballCountText);
    window.draw(gameTopBar.ballCountNum);

    window.draw(gameTopBar.scoreText);
    window.draw(gameTopBar.scoreNum);
}

// Отрисовка игрового поля
void drawGameField(RenderWindow &window, GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT; ++i)
    {
        window.draw(gameField.cells[i].shape);
        if (gameField.cells[i].ball != nullptr)
        {
            window.draw(*(gameField.cells[i].ball));
        }
    }
}

// Отрисовка объектов на форме
void drawObjects(RenderWindow &window, GameView &gameView)
{
    drawGameField(window, gameView.gameField);
    drawGameTopBar(window, gameView.gameTopBar);
    window.display();
}

// Обновление Формы
void update(RenderWindow &window, GameView &gameView)
{
    drawObjects(window, gameView);
    window.clear(Color::Black);
}

// Игровой цикл
void gameLoop(RenderWindow &window, GameView &gameView)
{
    while (window.isOpen())
    {
        handleEvents(window, gameView);
        update(window, gameView);
    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE, Style::Close, settings);
    Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    GameView gameView;
    initGameView(gameView, windowCenter);

    addBalls(gameView);

    gameLoop(window, gameView);

    return 0;
}