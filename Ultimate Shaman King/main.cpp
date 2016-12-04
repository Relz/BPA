#include "stdafx.h"
#include "handleEvents.h"
#include "Yoh.h"

using namespace sf;

// Отрисовка объектов на форме
void drawObjects(RenderWindow &window, CYoh &yoh)
{
    window.draw(*yoh.getModel());
    window.display();
}

// Отрисовка формы
void render(RenderWindow &window, CYoh &yoh)
{
    drawObjects(window, yoh);
    window.clear(BACKGROUND_COLOR);
}

// Обновление объектов
void update(CYoh &yoh)
{
    yoh.update();
}

// Игровой цикл
void gameLoop(RenderWindow &window, CYoh &yoh)
{
    while (window.isOpen())
    {
        handleEvents(window, yoh);
        update(yoh);
        render(window, yoh);
    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE, Style::Close, settings);
    window.setFramerateLimit(FPS);

    CYoh yoh(START_POS_YOH);
    gameLoop(window, yoh);

    return 0;
}