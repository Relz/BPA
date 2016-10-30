#include "handleEvents.h"

// Обработка нажатия левой кнопкой мыши
void processLeftMouseButtonClick(GameField &gameField, size_t clickX, size_t clickY)
{
    if (doesUserClickedOnField(gameField, clickX, clickY))
    {
        Cell *cell = &getCellByPos(gameField, clickX, clickY);
        if (cell->ball != nullptr) // Если у нажатой ячейки есть шар
        {
            selectBall(gameField, cell);
        }
        else if (gameField.selectedCell != nullptr) // Если нажатая ячейка пуста и уже выбран шар
        {
            moveBall(gameField, cell);
            if (wasLineFoundAndRemoved(gameField, cell))
            {

            }
            else
            {
                addBalls(gameField);
            }
        }
    }
}

// Обработка событий на форме
void handleEvents(RenderWindow &window, GameField &gameField)
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
                    processLeftMouseButtonClick(gameField, event.mouseButton.x, event.mouseButton.y);
                }
                break;
            }
            default:
                break;
        }
    }
}