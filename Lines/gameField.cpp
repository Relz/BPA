#include "gameField.h"

// Функция высчитывания кол-ва шариков сверху и сохранения позиций шариков для дальнейшего возможного удаления
size_t countUpperBalls(GameField &gameField, const PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift <= cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }
    return result;
}

// Функция высчитывания кол-ва шариков снизу и сохранения позиций шариков для дальнейшего возможного удаления
size_t countLowerBalls(GameField &gameField, PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }
    return result;
}

// Функция проверки выстроенной в колонку LINE_BALL_COUNT шаров
bool wasVerticalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    ballCount += countUpperBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);
    ballCount += countLowerBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);

    if (ballCount < LINE_BALL_COUNT)
    {
        cellsToClear.erase(cellsToClear.begin() + breakPoint, cellsToClear.end());
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция высчитывания кол-ва шариков по диагонали направо-вверх и сохранения позиций шариков для дальнейшего возможного удаления
size_t countRightUpperBalls(GameField &gameField, PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x && shift <= cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x + shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }
    return result;
}

// Функция высчитывания кол-ва шариков по диагонали слева-вниз и сохранения позиций шариков для дальнейшего возможного удаления
size_t countLeftLowerBalls(GameField &gameField, PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift <= cellPosition.x && shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x - shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }

    return result;
}

// Функция проверки выстроенной по правой диагонали LINE_BALL_COUNT шаров
bool wasRightDiagonalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    ballCount += countRightUpperBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);
    ballCount += countLeftLowerBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);

    if (ballCount < LINE_BALL_COUNT)
    {
        cellsToClear.erase(cellsToClear.begin() + breakPoint, cellsToClear.end());
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция высчитывания кол-ва шариков снизу и сохранения позиций шариков для дальнейшего возможного удаления
size_t countRightBalls(GameField &gameField, PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x; ++shift)
    {
        size_t shiftedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x + shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }
    return result;
}

// Функция высчитывания кол-ва шариков снизу и сохранения позиций шариков для дальнейшего возможного удаления
size_t countLeftBalls(GameField &gameField, PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift <= cellPosition.x; ++shift)
    {
        size_t shiftedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x - shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }
    return result;
}

// Функция проверки выстроенной в ряд LINE_BALL_COUNT шаров
bool wasHorizontalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    ballCount += countRightBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);
    ballCount += countLeftBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);

    if (ballCount < LINE_BALL_COUNT)
    {
        cellsToClear.erase(cellsToClear.begin() + breakPoint, cellsToClear.end());
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция высчитывания кол-ва шариков по диагонали направо-вверх и сохранения позиций шариков для дальнейшего возможного удаления
size_t countRightLowerBalls(GameField &gameField, PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift < CELL_COUNT_X - cellPosition.x && shift < CELL_COUNT_Y - cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y + shift) * CELL_COUNT_X + cellPosition.x + shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }
    return result;
}

// Функция высчитывания кол-ва шариков по диагонали слева-вниз и сохранения позиций шариков для дальнейшего возможного удаления
size_t countLeftUpperBalls(GameField &gameField, PositionOnField &cellPosition, size_t clickedCellPosition, vector<Cell *> &cellsToClear)
{
    size_t result = 0;
    for (size_t shift = 1; shift <= cellPosition.x && shift <= cellPosition.y; ++shift)
    {
        size_t shiftedCellPosition = (cellPosition.y - shift) * CELL_COUNT_X + cellPosition.x - shift;
        if (gameField.cells[shiftedCellPosition].ball == nullptr ||
            gameField.cells[shiftedCellPosition].ball->getFillColor() != gameField.cells[clickedCellPosition].ball->getFillColor())
        {
            break;
        }
        cellsToClear.push_back(&gameField.cells[shiftedCellPosition]);
        result++;
    }
    return result;
}

// Функция проверки выстроенной по левой диагонали LINE_BALL_COUNT шаров
bool wasLeftDiagonalLineFound(GameField &gameField, PositionOnField &cellPosition, vector<Cell *> &cellsToClear)
{
    size_t ballCount = 1;
    size_t clickedCellPosition = cellPosition.y * CELL_COUNT_X + cellPosition.x;
    size_t breakPoint = cellsToClear.size();

    ballCount += countRightLowerBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);
    ballCount += countLeftUpperBalls(gameField, cellPosition, clickedCellPosition, cellsToClear);

    if (ballCount < LINE_BALL_COUNT)
    {
        cellsToClear.erase(cellsToClear.begin() + breakPoint, cellsToClear.end());
    }

    return (ballCount >= LINE_BALL_COUNT);
}

// Функция проверки выстроенной в линию LINE_BALL_COUNT шаров и последующего удаления этой линии
bool wasLineFoundAndRemoved(GameField &gameField, GameInfo &gameInfo, Cell *cell)
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
        gameInfo.ballCount -= cellsToClear.size();
        gameInfo.score += cellsToClear.size();
        for (auto cellToClear : cellsToClear)
        {
            gameField.freePositionsOnField.emplace_back(PositionOnField(cellToClear->pos.x, cellToClear->pos.y));
            delete cellToClear->ball;
            cellToClear->ball = nullptr;
        }
        return true;
    }
    return false;
}

// Удаление позиции из массива свободных позиций игрового поля
void removeFreePositionOnGameField(vector<PositionOnField> &freePositionsOnField, PositionOnField positionOnField)
{
    for (size_t i = 0; i < freePositionsOnField.size(); ++i)
    {
        if (freePositionsOnField[i].x == positionOnField.x &&
            freePositionsOnField[i].y == positionOnField.y)
        {
            freePositionsOnField.erase(freePositionsOnField.begin() + i);
            break;
        }
    }
}

// Получение случайной свободной позиции шара
bool getRandomFreeFieldPosition(GameField &gameField, PositionOnField &positionOnField)
{
    if (gameField.freePositionsOnField.empty())
    {
        return false;
    }
    RandomTool randomTool;
    size_t randomPositionOnField = randomTool.getRandomValue(0, gameField.freePositionsOnField.size() - 1);
    positionOnField = gameField.freePositionsOnField[randomPositionOnField];
    removeFreePositionOnGameField(gameField.freePositionsOnField, positionOnField);
    return true;
}

// Получение шара случайного цвета и координат игрового поля, на которых уже нет шара
bool getRandomBallPointerOnFreeFieldPosition(GameView &gameView, BallPointerOnField &ballPointerOnField)
{
    if (gameView.gameInfo.ballCount >= CELL_COUNT)
    {
        gameView.isGameOver = true;
        return false;
    }
    RandomTool randomTool;
    PositionOnField positionOnField;
    if (!getRandomFreeFieldPosition(gameView.gameField, positionOnField))
    {
        return false;
    }

    ballPointerOnField.ball = new CircleShape;
    ballPointerOnField.ball->setPosition(positionOnField.x * CELL_SIZE + gameView.gameField.x + (CELL_SIZE - FUTURE_BALL_DIAMETER) / 2,
                            positionOnField.y * CELL_SIZE + gameView.gameField.y + (CELL_SIZE - FUTURE_BALL_DIAMETER) / 2);
    ballPointerOnField.ball->setRadius(FUTURE_BALL_RADIUS);
    ballPointerOnField.ball->setFillColor(ballColors[randomTool.getRandomValue(0, ballColors.size() - 1)]);
    ballPointerOnField.pos = positionOnField;
    return true;
}

// Готовит шары случайного цвета следующего хода в случайных свободных местах игровой карты
void setRandomFutureBalls(GameView &gameView)
{
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        if (getRandomBallPointerOnFreeFieldPosition(gameView, gameView.gameField.futureBallsPositions[i]))
        {
            gameView.gameTopBar.futureBalls[i].setFillColor(gameView.gameField.futureBallsPositions[i].ball->getFillColor());
        }
    }
}

// Добавление шаров на игровое поле
void addBalls(GameView &gameView)
{
    if (gameView.gameInfo.ballCount >= CELL_COUNT)
    {
        gameView.isGameOver = true;
        return;
    }
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        size_t cellPos = gameView.gameField.futureBallsPositions[i].pos.y * CELL_COUNT_X + gameView.gameField.futureBallsPositions[i].pos.x;
        if (gameView.gameField.cells[cellPos].ball != nullptr)
        {
            if (!getRandomFreeFieldPosition(gameView.gameField, gameView.gameField.futureBallsPositions[i].pos))
            {
                return;
            }
            cellPos = gameView.gameField.futureBallsPositions[i].pos.y * CELL_COUNT_X + gameView.gameField.futureBallsPositions[i].pos.x;
        }

        gameView.gameField.futureBallsPositions[i].ball->setRadius(BALL_RADIUS);
        gameView.gameField.futureBallsPositions[i].ball->setPosition(
                gameView.gameField.futureBallsPositions[i].pos.x * CELL_SIZE + gameView.gameField.x + (CELL_SIZE - BALL_DIAMETER) / 2,
                gameView.gameField.futureBallsPositions[i].pos.y * CELL_SIZE + gameView.gameField.y + (CELL_SIZE - BALL_DIAMETER) / 2);
        gameView.gameField.cells[cellPos].ball = gameView.gameField.futureBallsPositions[i].ball;

        if (wasLineFoundAndRemoved(gameView.gameField, gameView.gameInfo, &gameView.gameField.cells[cellPos]))
        {
            gameView.gameTopBar.ballCountNum.setString(to_string(gameView.gameInfo.ballCount));
            gameView.gameTopBar.scoreNum.setString(to_string(gameView.gameInfo.score));
        }
        gameView.gameInfo.ballCount++;
        gameView.gameTopBar.ballCountNum.setString(String(to_string(gameView.gameInfo.ballCount)));
    }
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

// Построение массива движения шара
void createMovesArray(GameField &gameField, Cell &cell)
{
    if (cell.distance == 0)
    {
        return;
    }
    if ((cell.pos.y > 0) && gameField.cells[(cell.pos.y - 1) * CELL_COUNT_X + cell.pos.x].distance == cell.distance - 1)
    {
        gameField.moves.emplace_back(cell.pos);
        createMovesArray(gameField, gameField.cells[(cell.pos.y - 1) * CELL_COUNT_X + cell.pos.x]);
    }
    else if ((cell.pos.x < CELL_COUNT_X - 1) && gameField.cells[cell.pos.y * CELL_COUNT_X + cell.pos.x + 1].distance == cell.distance - 1)
    {
        gameField.moves.emplace_back(cell.pos);
        createMovesArray(gameField, gameField.cells[cell.pos.y * CELL_COUNT_X + cell.pos.x + 1]);
    }
    else if ((cell.pos.y < CELL_COUNT_Y - 1) && gameField.cells[(cell.pos.y + 1) * CELL_COUNT_X + cell.pos.x].distance == cell.distance - 1)
    {
        gameField.moves.emplace_back(cell.pos);
        createMovesArray(gameField, gameField.cells[(cell.pos.y + 1) * CELL_COUNT_X + cell.pos.x]);
    }
    else if ((cell.pos.x > 0) && gameField.cells[cell.pos.y * CELL_COUNT_X + cell.pos.x - 1].distance == cell.distance - 1)
    {
        gameField.moves.emplace_back(cell.pos);
        createMovesArray(gameField, gameField.cells[cell.pos.y * CELL_COUNT_X + cell.pos.x - 1]);
    }
}

// Построение карты дистанций от текущей клетки до конечной
void createDistanceMap(GameField &gameField, Cell current, Cell &cell)
{
    if (current.pos.x == cell.pos.x && current.pos.y == cell.pos.y)
    {
        return;
    }
    // Переход на клетку вверх
    size_t upperPos = (current.pos.y - 1) * CELL_COUNT_X + current.pos.x;
    if ((current.pos.y > 0) && ((gameField.cells[upperPos].distance == 0 &&
            (gameField.selectedCell->pos.x != current.pos.x ||
             gameField.selectedCell->pos.y != current.pos.y - 1) && gameField.cells[upperPos].ball == nullptr) ||
            gameField.cells[upperPos].distance > current.distance + 1))
    {
        gameField.cells[upperPos].distance = current.distance + 1;
        createDistanceMap(gameField, gameField.cells[upperPos], cell);
    }
    // Переход на клетку вправо
    size_t rightPos = current.pos.y * CELL_COUNT_X + current.pos.x + 1;
    if ((current.pos.x < CELL_COUNT_X - 1) && ((gameField.cells[rightPos].distance == 0 &&
            (gameField.selectedCell->pos.x != current.pos.x + 1 ||
             gameField.selectedCell->pos.y != current.pos.y) && gameField.cells[rightPos].ball == nullptr) ||
            gameField.cells[rightPos].distance > current.distance + 1))
    {
        gameField.cells[rightPos].distance = current.distance + 1;
        createDistanceMap(gameField, gameField.cells[rightPos], cell);
    }
    // Переход на клетку вниз
    size_t lowerPos = (current.pos.y + 1) * CELL_COUNT_X + current.pos.x;
    if ((current.pos.y < CELL_COUNT_Y - 1) && ((gameField.cells[lowerPos].distance == 0 &&
            (gameField.selectedCell->pos.x != current.pos.x ||
             gameField.selectedCell->pos.y != current.pos.y + 1) && gameField.cells[lowerPos].ball == nullptr) ||
            gameField.cells[lowerPos].distance > current.distance + 1))
    {
        gameField.cells[lowerPos].distance = current.distance + 1;
        createDistanceMap(gameField, gameField.cells[lowerPos], cell);
    }
    // Переход на клетку влево
    size_t leftPos = current.pos.y * CELL_COUNT_X + current.pos.x - 1;
    if ((current.pos.x > 0) && ((gameField.cells[leftPos].distance == 0 &&
            (gameField.selectedCell->pos.x != current.pos.x - 1 ||
             gameField.selectedCell->pos.y != current.pos.y) && gameField.cells[leftPos].ball == nullptr) ||
            gameField.cells[leftPos].distance > current.distance + 1))
    {
        gameField.cells[leftPos].distance = current.distance + 1;
        createDistanceMap(gameField, gameField.cells[leftPos], cell);
    }
}

// Очистка карты дистанций
void clearDistanceMap(GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_Y; ++i)
    {
        for (size_t j = 0; j < CELL_COUNT_X; ++j)
        {
            gameField.cells[i * CELL_COUNT_X + j].distance = 0;
        }
    }
}

// Инициализцаия движения шара
void initMoves(GameField &gameField, Cell *cell)
{
    createDistanceMap(gameField, *gameField.selectedCell, *cell);
    createMovesArray(gameField, *cell);
    clearDistanceMap(gameField);
}

// Получение направления движения шара
void getBallSpeedXY(GameField gameField, float &speedX, float &speedY)
{
    if (gameField.selectedCell->ball->getPosition().x != gameField.x + gameField.moves[gameField.moves.size() - 1].x * CELL_SIZE + (CELL_SIZE - BALL_DIAMETER) / 2)
    {
        speedX = (gameField.selectedCell->ball->getPosition().x < gameField.x + gameField.moves[gameField.moves.size() - 1].x * CELL_SIZE + (CELL_SIZE - BALL_DIAMETER) / 2) ? BALL_MOVEMENT_SPEED : -BALL_MOVEMENT_SPEED;
    }
    if (gameField.selectedCell->ball->getPosition().y != gameField.y + gameField.moves[gameField.moves.size() - 1].y * CELL_SIZE + (CELL_SIZE - BALL_DIAMETER) / 2)
    {
        speedY = (gameField.selectedCell->ball->getPosition().y < gameField.y + gameField.moves[gameField.moves.size() - 1].y * CELL_SIZE + (CELL_SIZE - BALL_DIAMETER) / 2) ? BALL_MOVEMENT_SPEED : -BALL_MOVEMENT_SPEED;
    }
}

// Процесс движения шара
void moveBall(GameView &gameView)
{
    gameView.gameField.selectedCell->ball->setOutlineThickness(0);
    gameView.gameField.selectedCell->ball->setOutlineColor(Color::Transparent);

    float speedX = 0;
    float speedY = 0;
    getBallSpeedXY(gameView.gameField, speedX, speedY);

    gameView.gameField.selectedCell->ball->setPosition(gameView.gameField.selectedCell->ball->getPosition().x + speedX, gameView.gameField.selectedCell->ball->getPosition().y + speedY);

    if (abs(gameView.gameField.selectedCell->ball->getPosition().x - (gameView.gameField.x + gameView.gameField.moves[gameView.gameField.moves.size() - 1].x * CELL_SIZE + (CELL_SIZE - BALL_DIAMETER) / 2)) < BALL_MOVEMENT_SPEED
        && abs(gameView.gameField.selectedCell->ball->getPosition().y - (gameView.gameField.y + gameView.gameField.moves[gameView.gameField.moves.size() - 1].y * CELL_SIZE + (CELL_SIZE - BALL_DIAMETER) / 2)) < BALL_MOVEMENT_SPEED)
    {
        size_t dstCellPosX = gameView.gameField.moves[0].x;
        size_t dstCellPosY = gameView.gameField.moves[0].y;
        gameView.gameField.moves.pop_back();
        if (gameView.gameField.moves.empty())
        {
            gameView.gameField.cells[dstCellPosY * CELL_COUNT_X + dstCellPosX].ball = gameView.gameField.selectedCell->ball;
            gameView.gameField.selectedCell->ball = nullptr;
            gameView.gameField.selectedCell = nullptr;
            if (wasLineFoundAndRemoved(gameView.gameField, gameView.gameInfo, &gameView.gameField.cells[dstCellPosY * CELL_COUNT_X + dstCellPosX]))
            {
                gameView.gameTopBar.ballCountNum.setString(to_string(gameView.gameInfo.ballCount));
                gameView.gameTopBar.scoreNum.setString(to_string(gameView.gameInfo.score));
            }
            else
            {
                addBalls(gameView);
                setRandomFutureBalls(gameView);
            }
        }
    }
}

// Получить ячейку, зная позицию x y
Cell &getCellByPos(GameField &gameField, float x, float y)
{
    size_t i = static_cast<size_t >(floor((y - gameField.y) / CELL_SIZE));
    size_t j = static_cast<size_t >(floor((x - gameField.x) / CELL_SIZE));
    return gameField.cells[i * CELL_COUNT_X + j];
}

// Очистка массива ячеек игрового поля
void clearGameFieldCells(GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_Y; ++i)
    {
        for (size_t j = 0; j < CELL_COUNT_X; ++j)
        {
            size_t cellPos = i * CELL_COUNT_X + j;
            gameField.cells[cellPos].ball = nullptr;
        }
    }
}

// Очистка массива шаров следующего хода
void clearFutureBalls(BallPointerOnField *futureBallsPositions)
{
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        if (futureBallsPositions[i].ball != nullptr)
        {
            delete futureBallsPositions[i].ball;
            futureBallsPositions[i].ball = nullptr;
        }
        futureBallsPositions[i].pos = PositionOnField(0, 0);
    }
}

// Очистка игрового поля
void clearGameField(GameField &gameField)
{
    clearGameFieldCells(gameField);
    clearFutureBalls(gameField.futureBallsPositions);
    initFreePositionsOnField(gameField.freePositionsOnField);
}