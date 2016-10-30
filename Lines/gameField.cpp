#include "gameField.h"

// Получение случайных координат игрового поля, на которых нет шара
void getRandomEmptyPositionOnField(GameField &gameField, RandomTool &randomTool, PositionOnField &positionOnField)
{
    do
    {
        positionOnField.x = randomTool.getRandomValue(0, CELL_COUNT_X - 1);
        positionOnField.y = randomTool.getRandomValue(0, CELL_COUNT_Y - 1);
    } while (gameField.cells[positionOnField.y * CELL_COUNT_X + positionOnField.x].ball != nullptr);
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
        PositionOnField ballPosition;
        getRandomEmptyPositionOnField(gameField, randomTool, ballPosition);
        size_t cellPos = ballPosition.y * CELL_COUNT_X + ballPosition.x;

        gameField.cells[cellPos].ball = new CircleShape;
        gameField.cells[cellPos].ball->setPosition(ballPosition.x * CELL_SIZE + gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                                                   ballPosition.y * CELL_SIZE + gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
        gameField.cells[cellPos].ball->setRadius(BALL_RADIUS);
        gameField.cells[cellPos].ball->setFillColor(ballColors[randomTool.getRandomValue(0, ballColors.size() - 1)]);
    }
    gameField.ballCount += BALLS_PER_COUP;
}

// Функция проверки выстроенной в колонку LINE_BALL_COUNT шаров
bool wasVerticalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;

    for (size_t shift = 1; shift <= cellPosition.y; ++shift)
    {
        if (gameField.cells[(cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[(cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x]);
        ballCount++;
    }

    for (size_t shift = 1; shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        if (gameField.cells[(cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[(cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x]);
        ballCount++;
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной по правой диагонали LINE_BALL_COUNT шаров
bool wasRightDiagonalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;

    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x && shift <= cellPosition.y; ++shift)
    {
        if (gameField.cells[(cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x + shift].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[(cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x + shift]);
        ballCount++;
    }

    for (size_t shift = 1; shift <= cellPosition.x && shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        if (gameField.cells[(cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x - shift].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[(cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x - shift]);
        ballCount++;
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной в ряд LINE_BALL_COUNT шаров
bool wasHorizontalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;

    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x; ++shift)
    {
        if (gameField.cells[cellPosition.y * CELL_COUNT_X + cellPosition.x + shift].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[cellPosition.y * CELL_COUNT_X + cellPosition.x + shift]);
        ballCount++;
    }

    for (size_t shift = 1; shift <= cellPosition.x; ++shift)
    {
        if (gameField.cells[cellPosition.y * CELL_COUNT_X + cellPosition.x - shift].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[cellPosition.y * CELL_COUNT_X + cellPosition.x - shift]);
        ballCount++;
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной по левой диагонали LINE_BALL_COUNT шаров
bool wasLeftDiagonalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;

    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x && shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        if (gameField.cells[(cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x + shift].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[(cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x + shift]);
        ballCount++;
    }

    for (size_t shift = 1; shift <= cellPosition.x && shift <= cellPosition.y; ++shift)
    {
        if (gameField.cells[(cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x - shift].ball == nullptr)
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[(cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x - shift]);
        ballCount++;
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной в линию LINE_BALL_COUNT шаров и последующего удаления этой линии
bool wasLineFoundAndRemoved(GameField &gameField, Cell *cell)
{
    PositionOnField cellPosition(cell->posX, cell->posY);
    vector<Cell *> cellsToClear({cell});
    if (wasVerticalLineFound(gameField, cellPosition, cellsToClear)
        || wasRightDiagonalLineFound(gameField, cellPosition, cellsToClear)
        || wasHorizontalLineFound(gameField, cellPosition, cellsToClear)
        || wasLeftDiagonalLineFound(gameField, cellPosition, cellsToClear))
    {
        for (auto cellToClear : cellsToClear)
        {
            delete cellToClear->ball;
            cellToClear->ball = nullptr;
        }
        return true;
    }
    return false;
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