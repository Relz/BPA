#include "gameView.h"

// Было ли произведено нажатие в пределах кнопки перезагрузки игры на экране конца игры
bool doesUserClickedOnRestartButtonOnGameOverView(Button &restartButton, size_t clickX, size_t clickY)
{
    return (clickY >= restartButton.shape.getPosition().y && clickY < restartButton.shape.getPosition().y + CELL_COUNT_Y * CELL_SIZE &&
            clickX >= restartButton.shape.getPosition().x && clickX < restartButton.shape.getPosition().x + CELL_COUNT_X * CELL_SIZE);
}

// Было ли произведено нажатие в пределах кнопки перезагрузки игры под игровым полем
bool doesUserClickedOnRestartButton(Button &restartButton, size_t clickX, size_t clickY)
{
    return (clickY >= restartButton.shape.getPosition().y && clickY < restartButton.shape.getPosition().y + CELL_COUNT_Y * CELL_SIZE &&
            clickX >= restartButton.shape.getPosition().x && clickX < restartButton.shape.getPosition().x + CELL_COUNT_X * CELL_SIZE);
}

// Было ли произведено нажатие в пределах игрового поля
bool doesUserClickedOnField(GameField &gameField, size_t clickX, size_t clickY)
{
    return (clickY >= gameField.y && clickY < gameField.y + CELL_COUNT_Y * CELL_SIZE &&
            clickX >= gameField.x && clickX < gameField.x + CELL_COUNT_X * CELL_SIZE);
}

// Перезагрузка игры
void restartGame(GameView &gameView)
{
    gameView.gameInfo.ballCount = 0;
    gameView.gameInfo.score = 0;
    gameView.gameTopBar.scoreNum.setString(to_string(gameView.gameInfo.score));
    gameView.isGameOver = false;
    clearGameField(gameView.gameField);

    setRandomFutureBalls(gameView);
    addBalls(gameView);
    setRandomFutureBalls(gameView);
}