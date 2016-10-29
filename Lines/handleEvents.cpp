#include "handleEvents.h"

// Получить ячейку, зная позицию x y
Cell &getCellByPos(GameField &gameField, float x, float y)
{
    size_t i = floor((y - gameField.y) / CELL_SIZE);
    size_t j = floor((x - gameField.x) / CELL_SIZE);
    return gameField.cells[i * CELL_COUNT_X + j];
}

// Было ли произведено нажатие в пределах игрового поля
bool doesUserClickedOnField(GameField &gameField, size_t clickX, size_t clickY)
{
    return (clickY >= gameField.y && clickY < gameField.y + CELL_COUNT_Y * CELL_SIZE &&
        clickX >= gameField.x && clickX < gameField.x + CELL_COUNT_X * CELL_SIZE);
}

// Обработка нажатия левой кнопкой мыши
void processLeftMouseButtonClick(GameField &gameField, size_t clickX, size_t clickY)
{
    if (doesUserClickedOnField(gameField, clickX, clickY))
    {
        Cell *cell = &getCellByPos(gameField, clickX, clickY);
        if (cell->ball != nullptr)
        {
            if (gameField.selectedCell != nullptr)
            {
                gameField.selectedCell->ball->setOutlineThickness(0);
                gameField.selectedCell->ball->setOutlineColor(Color::Transparent);
            }
            gameField.selectedCell = cell;
            gameField.selectedCell->ball->setOutlineThickness(CELL_OUTLINE_THICKNESS);
            gameField.selectedCell->ball->setOutlineColor(Color(0, 0, 0));
        }
        else if (gameField.selectedCell != nullptr)
        {
            gameField.selectedCell->ball->setPosition(cell->posX * CELL_SIZE + gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                                                      cell->posY * CELL_SIZE + gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
            gameField.selectedCell->ball->setOutlineThickness(0);
            gameField.selectedCell->ball->setOutlineColor(Color::Transparent);
            cell->ball = gameField.selectedCell->ball;
            gameField.selectedCell->ball = nullptr;
            gameField.selectedCell = nullptr;
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