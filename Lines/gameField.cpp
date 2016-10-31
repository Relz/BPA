#include "gameField.h"

// Функция проверки выстроенной в колонку LINE_BALL_COUNT шаров
bool wasVerticalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    for (size_t shift = 1; shift <= cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    for (size_t shift = 1; shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    if (ballCount < LINE_BALL_COUNT)
    {
        for (size_t i = breakPoint; i < cellsToClear.size(); ++i)
        {
            cellsToClear.pop_back();
        }
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной по правой диагонали LINE_BALL_COUNT шаров
bool wasRightDiagonalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x && shift <= cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x + shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    for (size_t shift = 1; shift <= cellPosition.x && shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x - shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    if (ballCount < LINE_BALL_COUNT)
    {
        for (size_t i = breakPoint; i < cellsToClear.size(); ++i)
        {
            cellsToClear.pop_back();
        }
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной в ряд LINE_BALL_COUNT шаров
bool wasHorizontalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x; ++shift)
    {
        size_t shiftedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x + shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    for (size_t shift = 1; shift <= cellPosition.x; ++shift)
    {
        size_t shiftedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x - shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    if (ballCount < LINE_BALL_COUNT)
    {
        for (size_t i = breakPoint; i < cellsToClear.size(); ++i)
        {
            cellsToClear.pop_back();
        }
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной по левой диагонали LINE_BALL_COUNT шаров
bool wasLeftDiagonalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x && shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x + shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    for (size_t shift = 1; shift <= cellPosition.x && shift <= cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x - shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        ballCount++;
    }

    if (ballCount < LINE_BALL_COUNT)
    {
        for (size_t i = breakPoint; i < cellsToClear.size(); ++i)
        {
            cellsToClear.pop_back();
        }
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной в линию LINE_BALL_COUNT шаров и последующего удаления этой линии
bool wasLineFoundAndRemoved(GameField &gameField, Cell *cell)
{
    PositionOnField cellPosition(cell->pos.x, cell->pos.y);
    vector<Cell *> cellsToClear;
    bool lineFound = wasVerticalLineFound(gameField, cellPosition, cellsToClear);
    lineFound = wasRightDiagonalLineFound(gameField, cellPosition, cellsToClear) || lineFound;
    lineFound = wasHorizontalLineFound(gameField, cellPosition, cellsToClear) || lineFound;
    lineFound = wasLeftDiagonalLineFound(gameField, cellPosition, cellsToClear) || lineFound;
    if (lineFound)
    {
        cellsToClear.push_back(cell);
        gameField.ballCount -= cellsToClear.size();
        gameField.score += cellsToClear.size();
        for (auto cellToClear : cellsToClear)
        {
            delete cellToClear->ball;
            cellToClear->ball = nullptr;
        }
        return true;
    }
    return false;
}

// Получение случайной свободной позиции шара
void getRandomFreeFieldPosition(GameField &gameField, PositionOnField &positionOnField)
{
    RandomTool randomTool;
    do
    {
        positionOnField.x = randomTool.getRandomValue(0, CELL_COUNT_X - 1);
        positionOnField.y = randomTool.getRandomValue(0, CELL_COUNT_Y - 1);
    } while (gameField.cells[positionOnField.y * CELL_COUNT_X + positionOnField.x].ball != nullptr);
}

// Получение шара случайного цвета и координат игрового поля, на которых уже нет шара
void getRandomBallPointerOnFreeFieldPosition(GameField &gameField, BallPointerOnField &ballPointerOnField)
{
    RandomTool randomTool;
    PositionOnField positionOnField;
    getRandomFreeFieldPosition(gameField, positionOnField);

    size_t cellPos = positionOnField.y * CELL_COUNT_X + positionOnField.x;

    ballPointerOnField.ball = new CircleShape;
    ballPointerOnField.ball->setPosition(positionOnField.x * CELL_SIZE + gameField.x + (CELL_SIZE - FUTURE_BALL_DIAMETER) / 2,
                            positionOnField.y * CELL_SIZE + gameField.y + (CELL_SIZE - FUTURE_BALL_DIAMETER) / 2);
    ballPointerOnField.ball->setRadius(FUTURE_BALL_RADIUS);
    ballPointerOnField.ball->setFillColor(ballColors[randomTool.getRandomValue(0, ballColors.size() - 1)]);
    ballPointerOnField.pos = positionOnField;
}

void setRandomFutureBalls(GameView &gameView)
{
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        getRandomBallPointerOnFreeFieldPosition(gameView.gameField, gameView.gameField.futureBallsPositions[i]);
        gameView.gameTopBar.futureBalls[i].setFillColor(gameView.gameField.futureBallsPositions[i].ball->getFillColor());
    }
}

// Добавление шаров на игровое поле
void addBalls(GameView &gameView)
{
    if (gameView.gameField.ballCount == CELL_COUNT)
    {
        return;
    }
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        if (gameView.gameField.cells[gameView.gameField.futureBallsPositions[i].pos.y * CELL_COUNT_X + gameView.gameField.futureBallsPositions[i].pos.x].ball != nullptr)
        {
            getRandomFreeFieldPosition(gameView.gameField, gameView.gameField.futureBallsPositions[i].pos);
        }
        gameView.gameField.futureBallsPositions[i].ball->setRadius(BALL_RADIUS);
        gameView.gameField.futureBallsPositions[i].ball->setPosition(
                gameView.gameField.futureBallsPositions[i].pos.x * CELL_SIZE + gameView.gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                gameView.gameField.futureBallsPositions[i].pos.y * CELL_SIZE + gameView.gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
        gameView.gameField.cells[gameView.gameField.futureBallsPositions[i].pos.y * CELL_COUNT_X + gameView.gameField.futureBallsPositions[i].pos.x].ball = gameView.gameField.futureBallsPositions[i].ball;
    }
    gameView.gameField.ballCount += BALLS_PER_COUP;
    gameView.gameTopBar.ballCountNum.setString(String(to_string(gameView.gameField.ballCount)));
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
    gameField.selectedCell->ball->setPosition(cell->pos.x * CELL_SIZE + gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                                              cell->pos.y * CELL_SIZE + gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
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