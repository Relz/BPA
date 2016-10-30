#include "gameField.h"

// Получение случайных координат игрового поля, на которых нет шара
void getRandomEmptyFieldPosition(GameField &gameField, RandomTool &randomTool, FieldPosition &fieldPosition)
{
    do
    {
        fieldPosition.x = randomTool.getRandomValue(0, CELL_COUNT_X - 1);
        fieldPosition.y = randomTool.getRandomValue(0, CELL_COUNT_Y - 1);
    } while (gameField.cells[fieldPosition.y * CELL_COUNT_X + fieldPosition.x].ball != nullptr);
}

// Добавление шаров на игровое поле
void addBalls(GameField &gameField)
{
    if (gameField.ballCount == CELL_COUNT)
    {
        return;
    }
    RandomTool randomTool;
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        FieldPosition fieldPosition;
        getRandomEmptyFieldPosition(gameField, randomTool, fieldPosition);
        size_t cellPos = fieldPosition.y * CELL_COUNT_X + fieldPosition.x;

        gameField.cells[cellPos].ball = new CircleShape;
        gameField.cells[cellPos].ball->setPosition(fieldPosition.x * CELL_SIZE + gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                                                   fieldPosition.y * CELL_SIZE + gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
        gameField.cells[cellPos].ball->setRadius(BALL_RADIUS);
        gameField.cells[cellPos].ball->setFillColor(ballColors[randomTool.getRandomValue(0, ballColors.size() - 1)]);
    }
    gameField.ballCount += BALLS_PER_COUP;
}

/*TODO: Передавать в функции проверки выстроения шаров в одну линию Vector2f позицию нажатой клетки*/

// Функция проверки выстроенной в ряд LINE_BALL_COUNT шаров
bool wasHorizontalLineFound(GameField &gameField, Cell *cell)
{
    size_t ballCount = 1;
    for (size_t shift = 1; shift < CELL_COUNT_X - cell->posX && ballCount != LINE_BALL_COUNT; ++shift)
    {
        if (gameField.cells[cell->posY * CELL_COUNT_X + cell->posX + shift].ball == nullptr)
        {
            break;
        }
        ballCount++;
    }

    if (ballCount == LINE_BALL_COUNT)
    {
        return true;
    }

    for (size_t shift = 1; shift < cell->posX && ballCount != LINE_BALL_COUNT; ++shift)
    {
        if (gameField.cells[cell->posY * CELL_COUNT_X + cell->posX - shift].ball == nullptr)
        {
            break;
        }
        ballCount++;
    }

    return (ballCount == LINE_BALL_COUNT);
}

// Функция проверки выстроенной в линию LINE_BALL_COUNT шаров и последующего удаления этой линии
bool wasLineFoundAndRemoved(GameField &gameField, Cell *cell)
{
    return wasHorizontalLineFound(gameField, cell);
}

// Выбрать шар
void selectBall(GameField &gameField, Cell *cell)
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

// Переместить шар
void moveBall(GameField &gameField, Cell *cell)
{
    gameField.selectedCell->ball->setPosition(cell->posX * CELL_SIZE + gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                                              cell->posY * CELL_SIZE + gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
    gameField.selectedCell->ball->setOutlineThickness(0);
    gameField.selectedCell->ball->setOutlineColor(Color::Transparent);
    cell->ball = gameField.selectedCell->ball;
    gameField.selectedCell->ball = nullptr;
    gameField.selectedCell = nullptr;
}

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