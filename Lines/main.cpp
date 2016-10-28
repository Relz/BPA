#include "stdafx.h"
#include "constant.h"

// Отрисовка объектов на форме
void drawObjects(RenderWindow &window/*, MyClock &clock*/)
{
    window.display();
}

// Обновление Формы
void update(RenderWindow &window)
{
    drawObjects(window);    window.clear(Color::White);

}

// Обработка событий на форме
void handleEvents(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();
    }
}

// Игровой цикл
void gameLoop(RenderWindow &window)
{
    while (window.isOpen())
    {
        handleEvents(window);
        update(window);
    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE, Style::Close, settings);

    gameLoop(window);

    return 0;
}