#include "handleEvents.h"

// Обработка нажатия левой кнопкой мыши
void processLeftMouseButtonClick(GameView &gameView, size_t clickX, size_t clickY)
{
    if (!gameView.isGameOver)
    {
        if (doesUserClickedOnField(gameView.gameField, clickX, clickY) && gameView.gameField.moves.empty())
        {
            Cell *cell = &getCellByPos(gameView.gameField, clickX, clickY);
            if (cell->ball != nullptr) // Если у нажатой ячейки есть шар
            {
                selectBall(gameView.gameField, cell);
            }
            else if (gameView.gameField.selectedCell != nullptr) // Если нажатая ячейка пуста и уже выбран шар
            {
                removeFreePositionOnGameField(gameView.gameField.freePositionsOnField,
                                              PositionOnField(cell->pos.x, cell->pos.y));
                gameView.gameField.freePositionsOnField.emplace_back(
                        PositionOnField(gameView.gameField.selectedCell->pos.x,
                                        gameView.gameField.selectedCell->pos.y));
                initMoves(gameView.gameField, cell);
            }
        }
        else if (doesUserClickedOnButton(gameView.gameBottomBar.restartButton, clickX, clickY))
        {
            restartGame(gameView);
        }
    }
    else if (doesUserClickedOnButton(gameView.gameOverView.restartButton, clickX, clickY))
    {
        restartGame(gameView);
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