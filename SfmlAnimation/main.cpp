﻿#include "stdafx.h"
#include "constant.h"

using namespace std;
using namespace sf;

struct Blocks
{
    RectangleShape rectangles[RECTANGLE_COUNT];
    Vector2f currentSize;
    Color currentRGBA;
    float currentRotation;
    unsigned mode = 0;
};

// Проверка блоков на столкновение со стеной
bool doesBlocksCollideWithWall(Blocks &blocks)
{
    float firstRectangleFutureX = blocks.rectangles[0].getPosition().x + ANIMATION_MODES[blocks.mode]["SPEED_X"];
    float firstRectangleFutureY = blocks.rectangles[0].getPosition().y + ANIMATION_MODES[blocks.mode]["SPEED_Y"];
    float lastRectangleFutureX = blocks.rectangles[RECTANGLE_COUNT - 1].getPosition().x + ANIMATION_MODES[blocks.mode]["SPEED_X"];
    float lastRectangleFutureY = blocks.rectangles[RECTANGLE_COUNT - 1].getPosition().y + ANIMATION_MODES[blocks.mode]["SPEED_Y"];

    return ((firstRectangleFutureX - RECTANGLE_WIDTH / 2 < 0 || firstRectangleFutureX + RECTANGLE_WIDTH / 2 > SCREEN_WIDTH)
        || (firstRectangleFutureY - RECTANGLE_HEIGHT / 2 < 0 || firstRectangleFutureY + RECTANGLE_HEIGHT / 2 > SCREEN_HEIGHT)
        || (lastRectangleFutureX - RECTANGLE_WIDTH / 2 < 0 || lastRectangleFutureX + RECTANGLE_WIDTH / 2 > SCREEN_WIDTH)
        || (lastRectangleFutureY - RECTANGLE_HEIGHT / 2 < 0 || lastRectangleFutureY + RECTANGLE_HEIGHT / 2 > SCREEN_HEIGHT));
}

// Инициализация прямоугольников
void initializeBlocks(Blocks &blocks)
{
    blocks.currentRGBA = START_COLOR;
    blocks.currentSize = Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
    blocks.currentRotation = blocks.rectangles[0].getRotation();
    for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
    {
        RectangleShape *rectangle = &blocks.rectangles[i];
        rectangle->setSize(blocks.currentSize);
        rectangle->setFillColor(blocks.currentRGBA);
        rectangle->setOrigin(RECTANGLE_WIDTH / 2, RECTANGLE_HEIGHT / 2);
        rectangle->setPosition(START_LEFT_OFFSET + rectangle->getOrigin().x,
                               ((RECTANGLE_HEIGHT + RECTANGLE_DISTANCE) * i) + START_TOP_OFFSET + rectangle->getOrigin().y);
    }
}

// Перевод градусов в радианы
float degreesToRadians(float degrees)
{
    return degrees * M_PI / 180;
}

// Асинхронный эффект: Поворот всех блоков вокруг оси первого
void rotateBlocks(Blocks &blocks)
{
    if (blocks.currentRotation != ANIMATION_MODES[blocks.mode]["ROTATION"])
    {
        if (blocks.currentRotation > ANIMATION_MODES[blocks.mode]["ROTATION"])
        {
            blocks.currentRotation -= SPEED_ROTATION;
        }
        else if (blocks.currentRotation < ANIMATION_MODES[blocks.mode]["ROTATION"])
        {
            blocks.currentRotation += SPEED_ROTATION;
        }
        for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
        {
            RectangleShape *rectangle = &blocks.rectangles[i];
            float dx = rectangle->getPosition().x - blocks.rectangles[0].getPosition().x;
            float dy = rectangle->getPosition().y - blocks.rectangles[0].getPosition().y;
            float distance = hypot(dx, dy);
            rectangle->setPosition(
                    distance * sin(degreesToRadians(blocks.currentRotation)) + blocks.rectangles[0].getPosition().x,
                    distance * cos(degreesToRadians(blocks.currentRotation)) + blocks.rectangles[0].getPosition().y);
            rectangle->setRotation(-blocks.currentRotation);
        }
    }
}

// Обновление ширины блока
void refreshBlockWidth(float &width, unsigned mode)
{
    if (width < ANIMATION_MODES[mode]["WIDTH"])
    {
        width += SPEED_SIZE;
    }
    else if (width > ANIMATION_MODES[mode]["WIDTH"])
    {
        width -= SPEED_SIZE;
    }
}

// Обновление высоты блока
void refreshBlockHeight(float &height, unsigned mode)
{
    if (height < ANIMATION_MODES[mode]["HEIGHT"])
    {
        height += SPEED_SIZE;
    }
    else if (height > ANIMATION_MODES[mode]["HEIGHT"])
    {
        height -= SPEED_SIZE;
    }
}

// Обновление размера блоков
void refreshBlocksSize(Blocks &blocks, Vector2f &currentSize)
{
    if (currentSize.x != ANIMATION_MODES[blocks.mode]["WIDTH"] || currentSize.y != ANIMATION_MODES[blocks.mode]["HEIGHT"])
    {
        for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
        {
            refreshBlockWidth(currentSize.x, blocks.mode);
            refreshBlockHeight(currentSize.y, blocks.mode);

            RectangleShape *rectangle = &blocks.rectangles[i];
            rectangle->setPosition(rectangle->getPosition().x,
                                   ((blocks.currentSize.y + RECTANGLE_DISTANCE) * i) + blocks.rectangles[0].getPosition().y);
            rectangle->setSize(currentSize);
        }
    }
}

// Обновление цвета и прозрачности блоков
void refreshBlocksColor(Uint8 &currentColor, const string &colorStr, unsigned mode)
{
    if (static_cast<int>(currentColor) < ANIMATION_MODES[mode][colorStr])
    {
        currentColor = Uint8(static_cast<int>(currentColor) + SPEED_COLOR);
    }
    else if (static_cast<int>(currentColor) > ANIMATION_MODES[mode][colorStr])
    {
        currentColor = Uint8(static_cast<int>(currentColor) - SPEED_COLOR);
    }
}

// Обновление цвета блоков
void refreshBlocksColors(Blocks &blocks)
{
    refreshBlocksColor(blocks.currentRGBA.r, "COLOR_RED", blocks.mode);
    refreshBlocksColor(blocks.currentRGBA.g, "COLOR_GREEN", blocks.mode);
    refreshBlocksColor(blocks.currentRGBA.b, "COLOR_BLUE", blocks.mode);
    refreshBlocksColor(blocks.currentRGBA.a, "OPACITY", blocks.mode);
}

// Движение блоков
void moveBlocks(Blocks &blocks)
{
    for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
    {
        RectangleShape *rectangle = &blocks.rectangles[i];
        rectangle->setPosition(rectangle->getPosition().x + ANIMATION_MODES[blocks.mode]["SPEED_X"],
                                         rectangle->getPosition().y + ANIMATION_MODES[blocks.mode]["SPEED_Y"]);
        rectangle->setFillColor(blocks.currentRGBA);
    }
}

// Обновление координат блоков
void refreshBlocks(Blocks &blocks)
{
    refreshBlocksColors(blocks);
    rotateBlocks(blocks);
    refreshBlocksSize(blocks, blocks.currentSize);
    moveBlocks(blocks);
}

// Отрисовка прямоугольников
void drawRectangles(RenderWindow &window, RectangleShape *rectangles)
{
    for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
    {
        window.draw(rectangles[i]);
    }
}

// Обновление Формы
void update(RenderWindow &window, RectangleShape *rectangles)
{
    window.clear(Color::White);
    drawRectangles(window, rectangles);
    window.display();
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
void processAnimation(RenderWindow &window, Blocks &blocks)
{
    while (window.isOpen())
    {
        handleEvents(window);

        if (blocks.mode != ANIMATION_MODES.size())
        {
            refreshBlocks(blocks);
        }
        if (doesBlocksCollideWithWall(blocks) && (blocks.mode + 1 != ANIMATION_MODES.size()))
        {
            blocks.mode++;
        }
        update(window, blocks.rectangles);
    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE, Style::Close, settings);
    Blocks blocks;
    
    initializeBlocks(blocks);
    
    processAnimation(window, blocks);

    return 0;
}