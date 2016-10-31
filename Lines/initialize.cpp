#include "initialize.h"

// Инициализация верхней панели
void initGameTopBar(GameView &gameView)
{
    if (!gameView.gameTopBar.font.loadFromFile("a_LCDNovaObl.ttf"))
    {
        cout << "Problems with font loading";
        return;
    }
    gameView.gameTopBar.ballCountText.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.ballCountText.setString(TEXT_BALLS);
    gameView.gameTopBar.ballCountText.setCharacterSize(20);
    gameView.gameTopBar.ballCountText.setPosition(gameView.gameField.x,
                                                  (gameView.gameField.y - gameView.gameTopBar.ballCountText.getLocalBounds().height) / 2);

    gameView.gameTopBar.ballCountNum.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.ballCountNum.setString(to_string(gameView.gameField.ballCount));
    gameView.gameTopBar.ballCountNum.setCharacterSize(50);
    gameView.gameTopBar.ballCountNum.setStyle(Text::Bold);
    gameView.gameTopBar.ballCountNum.setPosition(gameView.gameField.x + gameView.gameTopBar.ballCountText.getLocalBounds().width,
                                                 (gameView.gameField.y - gameView.gameTopBar.ballCountNum.getLocalBounds().height) / 2);

    gameView.gameTopBar.scoreNum.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.scoreNum.setString(to_string(gameView.gameField.score));
    gameView.gameTopBar.scoreNum.setCharacterSize(50);
    gameView.gameTopBar.scoreNum.setStyle(Text::Bold);
    gameView.gameTopBar.scoreNum.setPosition(gameView.gameField.x + CELL_COUNT_X * CELL_SIZE - gameView.gameTopBar.scoreNum.getLocalBounds().width,
                                             (gameView.gameField.y - gameView.gameTopBar.scoreNum.getLocalBounds().height) / 2);

    gameView.gameTopBar.scoreText.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.scoreText.setString(TEXT_SCORE);
    gameView.gameTopBar.scoreText.setCharacterSize(20);
    gameView.gameTopBar.scoreText.setPosition(gameView.gameField.x + CELL_COUNT_X * CELL_SIZE - gameView.gameTopBar.scoreNum.getLocalBounds().width - gameView.gameTopBar.scoreText.getLocalBounds().width,
                                              (gameView.gameField.y - gameView.gameTopBar.scoreText.getLocalBounds().height) / 2);
}

// Инициализация игровых ячеек
void initCells(GameField &gameField)
{
    for (size_t i = 0; i < CELL_COUNT_Y; ++i)
    {
        for (size_t j = 0; j < CELL_COUNT_X; ++j)
        {
            size_t cellPos = i * CELL_COUNT_X + j;
            gameField.cells[cellPos].shape.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
            gameField.cells[cellPos].shape.setFillColor(CELL_FILL_COLOR);
            gameField.cells[cellPos].shape.setOutlineThickness(CELL_OUTLINE_THICKNESS);
            gameField.cells[cellPos].shape.setOutlineColor(CELL_OUTLINE_COLOR);
            gameField.cells[cellPos].shape.setPosition(j * CELL_SIZE + gameField.x, i * CELL_SIZE + gameField.y);
            gameField.cells[cellPos].posX = j;
            gameField.cells[cellPos].posY = i;
            gameField.cells[cellPos].ball = nullptr;
        }
    }
}

// Инициализация игрового поля
void initGameField(GameField &gameField, Vector2f &windowCenter)
{
    gameField.x = windowCenter.x - CELL_COUNT_X * CELL_SIZE / 2;
    gameField.y = windowCenter.y - CELL_COUNT_Y * CELL_SIZE / 2;
    initCells(gameField);
}

void initGameView(GameView &gameView, Vector2f &windowCenter)
{
    initGameField(gameView.gameField, windowCenter);
    initGameTopBar(gameView);
}