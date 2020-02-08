#include "gameView.h"

// Было ли произведено нажатие в пределах кнопки
bool doesUserClickedOnButton(Button &restartButton, size_t clickX, size_t clickY)
{
    return (clickY >= restartButton.shape.getPosition().y && clickY < restartButton.shape.getPosition().y + restartButton.shape.getLocalBounds().height &&
            clickX >= restartButton.shape.getPosition().x && clickX < restartButton.shape.getPosition().x + restartButton.shape.getLocalBounds().width);
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