#include "handleEvents.h"

// Получить шарик ячеки, зная позицию x y
CircleShape &getCellBallByPos(GameField &gameField, float x, float y)
{
    size_t i = floor((y - gameField.y) / CELL_SIZE);
    size_t j = floor((x - gameField.x) / CELL_SIZE);
    return gameField.cells[i * CELL_COUNT_X + j].ball;
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
                    getCellBallByPos(gameField, event.mouseButton.x, event.mouseButton.y).setFillColor(Color(100, 0, 0));
                }
                break;
            }
            default:
                break;
        }
    }
}