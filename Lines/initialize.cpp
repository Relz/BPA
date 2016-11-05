#include "initialize.h"

// Инициализцаия отображения кол-ва шаров на верхней панели
void initBallCountInfoOnTopBar(GameView &gameView)
{
    gameView.gameTopBar.ballCountText.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.ballCountText.setString(TEXT_BALLS);
    gameView.gameTopBar.ballCountText.setCharacterSize(20);
    gameView.gameTopBar.ballCountText.setPosition(gameView.gameField.x,
                                                  (gameView.gameField.y - gameView.gameTopBar.ballCountText.getLocalBounds().height) / 2);

    gameView.gameTopBar.ballCountNum.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.ballCountNum.setString(to_string(gameView.gameInfo.ballCount));
    gameView.gameTopBar.ballCountNum.setCharacterSize(50);
    gameView.gameTopBar.ballCountNum.setStyle(Text::Bold);
    gameView.gameTopBar.ballCountNum.setPosition(gameView.gameField.x + gameView.gameTopBar.ballCountText.getLocalBounds().width,
                                                 (gameView.gameField.y - gameView.gameTopBar.ballCountNum.getLocalBounds().height) / 2);
}

// Инициализация отображения шаров следующего хода
void initFutureBallsOnTopBar(GameView &gameView)
{
    float posY = (gameView.gameField.y - BALL_RADIUS) / 2;
    float fieldCenter = gameView.gameField.x + (CELL_COUNT_X * CELL_SIZE / 2);
    for (size_t i = 0; i < BALLS_PER_COUP; ++i)
    {
        float posX = fieldCenter + BALL_DIAMETER + TOPBAR_FUTURE_BALLS_LEFT_PADDING - (BALLS_PER_COUP - i - 1) * (BALL_DIAMETER + TOPBAR_FUTURE_BALLS_LEFT_PADDING);
        gameView.gameTopBar.futureBalls[i].setRadius(BALL_RADIUS);
        gameView.gameTopBar.futureBalls[i].setPosition(posX, posY);
        gameView.gameTopBar.futureBalls[i].setOrigin(BALL_RADIUS, 0);
    }
}

// Инициализцаия отображения счёта на верхней панели
void initScoreInfoOnTopBar(GameView &gameView)
{
    gameView.gameTopBar.scoreNum.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.scoreNum.setString(to_string(gameView.gameInfo.score));
    gameView.gameTopBar.scoreNum.setCharacterSize(50);
    gameView.gameTopBar.scoreNum.setStyle(Text::Bold);
    gameView.gameTopBar.scoreNum.setPosition(gameView.gameField.x + CELL_COUNT_X * CELL_SIZE - gameView.gameTopBar.scoreNum.getLocalBounds().width * 2,
                                             (gameView.gameField.y - gameView.gameTopBar.scoreNum.getLocalBounds().height) / 2);

    gameView.gameTopBar.scoreText.setFont(gameView.gameTopBar.font);
    gameView.gameTopBar.scoreText.setString(TEXT_SCORE);
    gameView.gameTopBar.scoreText.setCharacterSize(20);
    gameView.gameTopBar.scoreText.setPosition(gameView.gameField.x + CELL_COUNT_X * CELL_SIZE - gameView.gameTopBar.scoreNum.getLocalBounds().width * 2 - gameView.gameTopBar.scoreText.getLocalBounds().width,
                                              (gameView.gameField.y - gameView.gameTopBar.scoreText.getLocalBounds().height) / 2);
}

// Инициализация верхней панели
bool initGameTopBar(GameView &gameView)
{
    if (!gameView.gameTopBar.font.loadFromFile("a_LCDNovaObl.ttf"))
    {
        cout << "Problems with font loading: file \"a_LCDNovaObl.ttf\" not found.";
        return false;
    }

    initBallCountInfoOnTopBar(gameView);
    initFutureBallsOnTopBar(gameView);
    initScoreInfoOnTopBar(gameView);
    return true;
}

// Инициализация кнопки перезагрузки игры на нижней панели
void initRestartButtonOnBottomBar(GameView &gameView, Vector2f &windowCenter)
{
    gameView.gameBottomBar.restartButton.text.setFont(gameView.gameBottomBar.font);
    gameView.gameBottomBar.restartButton.text.setString(TEXT_GAME_OVER_RESTART_BUTTON);
    gameView.gameBottomBar.restartButton.text.setCharacterSize(20);
    gameView.gameBottomBar.restartButton.text.setOutlineThickness(3);
    gameView.gameBottomBar.restartButton.text.setFillColor(RESTART_BUTTON_TEXT_COLOR);
    gameView.gameBottomBar.restartButton.text.setPosition(windowCenter.x - gameView.gameBottomBar.restartButton.text.getLocalBounds().width / 2,
                                                          gameView.gameField.y + CELL_COUNT_Y * CELL_SIZE + 10);
    gameView.gameBottomBar.restartButton.shape.setSize(Vector2f(gameView.gameBottomBar.restartButton.text.getLocalBounds().width + 20,
                                                                gameView.gameBottomBar.restartButton.text.getLocalBounds().height + 10));
    gameView.gameBottomBar.restartButton.shape.setFillColor(RESTART_BUTTON_FILL_COLOR);
    gameView.gameBottomBar.restartButton.shape.setOutlineThickness(2);
    gameView.gameBottomBar.restartButton.shape.setOutlineColor(RESTART_BUTTON_OUTLINE_COLOR);
    gameView.gameBottomBar.restartButton.shape.setPosition(gameView.gameBottomBar.restartButton.text.getPosition().x - 10,
                                                           gameView.gameBottomBar.restartButton.text.getPosition().y);
}

// Инициализация нижней панели
bool initGameBottomBar(GameView &gameView, Vector2f &windowCenter)
{
    if (!gameView.gameBottomBar.font.loadFromFile("DroidSans-Bold.ttf"))
    {
        cout << "Problems with font loading: file \"DroidSans-Bold.ttf\" not found.";
        return false;
    }

    initRestartButtonOnBottomBar(gameView, windowCenter);
    return true;
}

// Инициализация игровых ячеек
void initGameFieldCells(GameField &gameField)
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
            gameField.cells[cellPos].pos.x = j;
            gameField.cells[cellPos].pos.y = i;
        }
    }
}

// Инициализация массива свободных позиций игрового поля
void initFreePositionsOnField(vector<PositionOnField> &freePositionsOnField)
{
    freePositionsOnField = {};
    for (size_t i = 0; i < CELL_COUNT_Y; ++i)
    {
        for (size_t j = 0; j < CELL_COUNT_X; ++j)
        {
            freePositionsOnField.emplace_back(PositionOnField(j, i));
        }
    }
}

// Инициализация игрового поля
void initGameField(GameField &gameField, Vector2f &windowCenter)
{
    gameField.x = windowCenter.x - CELL_COUNT_X * CELL_SIZE / 2;
    gameField.y = windowCenter.y - CELL_COUNT_Y * CELL_SIZE / 2;
    initGameFieldCells(gameField);
    initFreePositionsOnField(gameField.freePositionsOnField);
}

// Инициализация фона экрана конца игры
void initGameOverViewBackground(RectangleShape &background)
{
    background.setSize(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    background.setFillColor(GAME_OVER_BACKGROUND_COLOR);
}

// Инициализация надписи конца игры
void initGameOverViewText(Text &gameOverText, Font &font, Vector2f &windowCenter)
{
    gameOverText.setFont(font);
    gameOverText.setString(TEXT_GAME_OVER);
    gameOverText.setCharacterSize(100);
    gameOverText.setOutlineThickness(5);
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setStyle(Text::Bold);
    gameOverText.setPosition(windowCenter.x - gameOverText.getLocalBounds().width / 2, windowCenter.y - gameOverText.getLocalBounds().height * 2);
}

// Инициализация надписи кол-ва очков на экране конца игры
void initGameOverViewScore(Text &scoreText, Font &font, Vector2f &windowCenter)
{
    scoreText.setFont(font);
    scoreText.setString(TEXT_GAME_OVER_SCORE);
    scoreText.setCharacterSize(90);
    scoreText.setOutlineThickness(5);
    scoreText.setOutlineColor(Color::Black);
    scoreText.setPosition(windowCenter.x - scoreText.getLocalBounds().width / 2, windowCenter.y);
}

// Инициализцаия кнопки перезагрузки игры на экране конца игры
void initGameOverViewRestartButton(Button &restartButton, Font &font, Vector2f &windowCenter)
{
    restartButton.text.setFont(font);
    restartButton.text.setString(TEXT_GAME_OVER_RESTART_BUTTON);
    restartButton.text.setCharacterSize(60);
    restartButton.text.setOutlineThickness(3);
    restartButton.text.setOutlineColor(GAME_OVER_RESTART_BUTTON_TEXT_OUTLINE_COLOR);
    restartButton.text.setPosition(windowCenter.x - restartButton.text.getLocalBounds().width / 2, SCREEN_HEIGHT - 100);
    restartButton.shape.setSize(Vector2f(restartButton.text.getLocalBounds().width + 20, restartButton.text.getLocalBounds().height + 30));
    restartButton.shape.setFillColor(GAME_OVER_RESTART_BUTTON_FILL_COLOR);
    restartButton.shape.setPosition(restartButton.text.getPosition().x - 10, restartButton.text.getPosition().y);
}

// Инициализация отображения конца игры
bool initGameOverView(GameView &gameView)
{
    if (!gameView.gameOverView.font.loadFromFile("DroidSans-Bold.ttf"))
    {
        cout << "Problems with font loading: file \"DroidSans-Bold.ttf\" not found.";
        return false;
    }
    initGameOverViewBackground(gameView.gameOverView.background);
    initGameOverViewText(gameView.gameOverView.gameOverText, gameView.gameOverView.font, gameView.windowCenter);
    initGameOverViewScore(gameView.gameOverView.scoreText, gameView.gameOverView.font, gameView.windowCenter);
    initGameOverViewRestartButton(gameView.gameOverView.restartButton, gameView.gameOverView.font, gameView.windowCenter);

    return true;
}

// Инициализация игрового экрана
bool initGameView(RenderWindow &window, GameView &gameView)
{
    gameView.windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    initGameField(gameView.gameField, gameView.windowCenter);
    return (initGameTopBar(gameView) && initGameBottomBar(gameView, gameView.windowCenter) && initGameOverView(gameView));
}