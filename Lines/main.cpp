#include "stdafx.h"

// Отрисовка верхней панели
void drawGameTopBar(RenderWindow &window, GameTopBar &gameTopBar)
{
    window.draw(gameTopBar.ballCountText);
    window.draw(gameTopBar.ballCountNum);

    window.draw(gameTopBar.scoreText);
    window.draw(gameTopBar.scoreNum);

    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        window.draw(gameTopBar.futureBalls[i]);
    }
}

// Отрисовка ячеек игрового поля
void drawCells(RenderWindow &window, Cell *cells)
{
    for (size_t i = 0; i < CELL_COUNT; ++i)
    {
        window.draw(cells[i].shape);
    }
}

// Отрисовка шаров на игровом поле
void drawBalls(RenderWindow &window, Cell *cells)
{
    for (size_t i = 0; i < CELL_COUNT; ++i)
    {
        if (cells[i].ball != nullptr)
        {
            window.draw(*(cells[i].ball));
        }
    }
}

// Отрисовка шаров следующего хода на игровом поле
void drawFutureBalls(RenderWindow &window, BallPointerOnField *futureBallsPositions)
{
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        window.draw(*(futureBallsPositions[i].ball));
    }
}

// Отрисовка игрового поля
void drawGameField(RenderWindow &window, GameField &gameField)
{
    drawCells(window, gameField.cells);
    drawFutureBalls(window, gameField.futureBallsPositions);
    drawBalls(window, gameField.cells);
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
        if (gameView.gameField.selectedCell != nullptr && !gameView.gameField.moves.empty())
        {
            moveBall(gameView);
        }
        else
        {
            handleEvents(window, gameView);
        }
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
    setRandomFutureBalls(gameView);
    addBalls(gameView);
    setRandomFutureBalls(gameView);

    gameLoop(window, gameView);

    return 0;
}