#include "handleEvents.h"

// Обработка нажатия левой кнопкой мыши
void processLeftMouseButtonClick(GameView &gameView, size_t clickX, size_t clickY)
{
    if (doesUserClickedOnField(gameView.gameField, clickX, clickY))
    {
        Cell *cell = &getCellByPos(gameView.gameField, clickX, clickY);
        if (cell->ball != nullptr) // Если у нажатой ячейки есть шар
        {
            selectBall(gameView.gameField, cell);
        }
        else if (gameView.gameField.selectedCell != nullptr) // Если нажатая ячейка пуста и уже выбран шар
        {
            moveBall(gameView.gameField, cell);
            if (wasLineFoundAndRemoved(gameView.gameField, cell))
            {
                gameView.gameTopBar.ballCountNum.setString(String(to_string(gameView.gameField.ballCount)));
                gameView.gameTopBar.scoreNum.setString(String(to_string(gameView.gameField.score)));
            }
            else
            {
                addBalls(gameView);
                setRandomFutureBalls(gameView);
            }
        }
    }
}

// Обработка событий на форме
void handleEvents(RenderWindow &window, GameView &gameView)
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
                    processLeftMouseButtonClick(gameView, event.mouseButton.x, event.mouseButton.y);
                }
                break;
            }
            default:
                break;
        }
    }
}