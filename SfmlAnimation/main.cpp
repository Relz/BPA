#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;
using namespace std;

const unsigned ANTIALIASING_LEVEL = 8;
const unsigned SCREEN_WIDTH = 540;
const unsigned SCREEN_HEIGHT = 600;

const unsigned RECTANGLE_COUNT = 8;
const unsigned RECTANGLE_WIDTH = 50;
const unsigned RECTANGLE_HEIGHT = 50;

const unsigned START_LEFT_OFFSET = 0;
const unsigned START_TOP_OFFSET = 10;

const unsigned RECTANGLE_DISTANCE = 10;

const float SPEED_X = 0.2;
const float SPEED_Y = 0.05;
const float SPEED_COLOR = 1;
const float SPEED_SIZE = 0.005;
const float SPEED_ROTATION = 0.005;

const Color START_COLOR = Color(0, 0, 100, 255);

unsigned mode = 0;

vector<map<string, map<string, float>>> ANIMATION_MODES =
        {
                {
                        pair<string, map<string, float>>("SPEED", {{"X", SPEED_X}, {"Y", 0}}),
                        pair<string, map<string, float>>("WIDTH", {{"TO", RECTANGLE_WIDTH}}),
                        pair<string, map<string, float>>("HEIGHT", {{"TO", RECTANGLE_HEIGHT}}),
                        pair<string, map<string, float>>("COLOR_RED", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_GREEN", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_BLUE", {{"TO", 100}}),
                        pair<string, map<string, float>>("OPACITY", {{"TO", 255}}),
                        pair<string, map<string, float>>("ROTATION", {{"TO", 0}})
                },
                {
                        pair<string, map<string, float>>("SPEED", {{"X", 0}, {"Y", SPEED_Y}}),
                        pair<string, map<string, float>>("WIDTH", {{"TO", RECTANGLE_WIDTH}}),
                        pair<string, map<string, float>>("HEIGHT", {{"TO", RECTANGLE_HEIGHT}}),
                        pair<string, map<string, float>>("COLOR_RED", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_GREEN", {{"TO", 100}}),
                        pair<string, map<string, float>>("COLOR_BLUE", {{"TO", 0}}),
                        pair<string, map<string, float>>("OPACITY", {{"TO", 255}}),
                        pair<string, map<string, float>>("ROTATION", {{"TO", 0}})
                },
                {
                        pair<string, map<string, float>>("SPEED", {{"X", -SPEED_X}, {"Y", -SPEED_Y}}),
                        pair<string, map<string, float>>("WIDTH", {{"TO", RECTANGLE_WIDTH}}),
                        pair<string, map<string, float>>("HEIGHT", {{"TO", RECTANGLE_HEIGHT}}),
                        pair<string, map<string, float>>("COLOR_RED", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_GREEN", {{"TO", 100}}),
                        pair<string, map<string, float>>("COLOR_BLUE", {{"TO", 0}}),
                        pair<string, map<string, float>>("OPACITY", {{"TO", 100}}),
                        pair<string, map<string, float>>("ROTATION", {{"TO", 0}})
                },
                {
                        pair<string, map<string, float>>("SPEED", {{"X", SPEED_X}, {"Y", 0}}),
                        pair<string, map<string, float>>("WIDTH", {{"TO", RECTANGLE_WIDTH}}),
                        pair<string, map<string, float>>("HEIGHT", {{"TO", RECTANGLE_HEIGHT / 2}}),
                        pair<string, map<string, float>>("COLOR_RED", {{"TO", 200}}),
                        pair<string, map<string, float>>("COLOR_GREEN", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_BLUE", {{"TO", 0}}),
                        pair<string, map<string, float>>("OPACITY", {{"TO", 100}}),
                        pair<string, map<string, float>>("ROTATION", {{"TO", 0}})
                },
                {
                        pair<string, map<string, float>>("SPEED", {{"X", 0}, {"Y", SPEED_Y}}),
                        pair<string, map<string, float>>("WIDTH", {{"TO", RECTANGLE_WIDTH / 5}}),
                        pair<string, map<string, float>>("HEIGHT", {{"TO", RECTANGLE_HEIGHT}}),
                        pair<string, map<string, float>>("COLOR_RED", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_GREEN", {{"TO", 100}}),
                        pair<string, map<string, float>>("COLOR_BLUE", {{"TO", 200}}),
                        pair<string, map<string, float>>("OPACITY", {{"TO", 255}}),
                        pair<string, map<string, float>>("ROTATION", {{"TO", 0}})
                },
                {
                        pair<string, map<string, float>>("SPEED", {{"X", -SPEED_X}, {"Y", -SPEED_Y}}),
                        pair<string, map<string, float>>("WIDTH", {{"TO", RECTANGLE_WIDTH}}),
                        pair<string, map<string, float>>("HEIGHT", {{"TO", RECTANGLE_HEIGHT}}),
                        pair<string, map<string, float>>("COLOR_RED", {{"TO", 100}}),
                        pair<string, map<string, float>>("COLOR_GREEN", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_BLUE", {{"TO", 20}}),
                        pair<string, map<string, float>>("OPACITY", {{"TO", 200}}),
                        pair<string, map<string, float>>("ROTATION", {{"TO", 0}})
                },
                {
                        pair<string, map<string, float>>("SPEED", {{"X", 0}, {"Y", 0}}),
                        pair<string, map<string, float>>("WIDTH", {{"TO", RECTANGLE_WIDTH}}),
                        pair<string, map<string, float>>("HEIGHT", {{"TO", RECTANGLE_HEIGHT}}),
                        pair<string, map<string, float>>("COLOR_RED", {{"TO", 100}}),
                        pair<string, map<string, float>>("COLOR_GREEN", {{"TO", 0}}),
                        pair<string, map<string, float>>("COLOR_BLUE", {{"TO", 20}}),
                        pair<string, map<string, float>>("OPACITY", {{"TO", 200}}),
                        pair<string, map<string, float>>("ROTATION", {{"TO", 90}})
                }
        };

struct Blocks
{
    RectangleShape rectangles[RECTANGLE_COUNT];
    Vector2f currentSize;
    Color currentRGBA;
    float currentRotation;
};

// Проверка блоков на столкновение со стеной
bool doesBlocksCollideWithWall(Blocks &blocks)
{
    float firstRectangleFutureX = blocks.rectangles[0].getPosition().x + ANIMATION_MODES[mode]["SPEED"]["X"];
    float firstRectangleFutureY = blocks.rectangles[0].getPosition().y + ANIMATION_MODES[mode]["SPEED"]["Y"];
    float lastRectangleFutureX = blocks.rectangles[RECTANGLE_COUNT - 1].getPosition().x + ANIMATION_MODES[mode]["SPEED"]["X"];
    float lastRectangleFutureY = blocks.rectangles[RECTANGLE_COUNT - 1].getPosition().y + ANIMATION_MODES[mode]["SPEED"]["Y"];

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
        blocks.rectangles[i].setSize(blocks.currentSize);
        blocks.rectangles[i].setFillColor(blocks.currentRGBA);
        blocks.rectangles[i].setOrigin(RECTANGLE_WIDTH / 2, RECTANGLE_HEIGHT / 2);
        blocks.rectangles[i].setPosition(START_LEFT_OFFSET + blocks.rectangles[i].getOrigin().x, ((RECTANGLE_HEIGHT + RECTANGLE_DISTANCE) * i) + START_TOP_OFFSET + blocks.rectangles[i].getOrigin().y);
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
    if (blocks.currentRotation != ANIMATION_MODES[mode]["ROTATION"]["TO"])
    {
        if (blocks.currentRotation > ANIMATION_MODES[mode]["ROTATION"]["TO"])
        {
            blocks.currentRotation -= SPEED_ROTATION;
        }
        else if (blocks.currentRotation < ANIMATION_MODES[mode]["ROTATION"]["TO"])
        {
            blocks.currentRotation += SPEED_ROTATION;
        }
        for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
        {
            float dx = blocks.rectangles[i].getPosition().x - blocks.rectangles[0].getPosition().x;
            float dy = blocks.rectangles[i].getPosition().y - blocks.rectangles[0].getPosition().y;
            float distance = hypot(dx, dy);
            blocks.rectangles[i].setPosition(
                    distance * sin(degreesToRadians(blocks.currentRotation)) + blocks.rectangles[0].getPosition().x,
                    distance * cos(degreesToRadians(blocks.currentRotation)) + blocks.rectangles[0].getPosition().y);
            blocks.rectangles[i].setRotation(-blocks.currentRotation);
        }
    }
}

// Обновление ширины блока
void refreshBlockWidth(float &width)
{
    if (width < ANIMATION_MODES[mode]["WIDTH"]["TO"])
    {
        width += SPEED_SIZE;
    }
    else if (width > ANIMATION_MODES[mode]["WIDTH"]["TO"])
    {
        width -= SPEED_SIZE;
    }
}

// Обновление высоты блока
void refreshBlockHeight(float &height)
{
    if (height < ANIMATION_MODES[mode]["HEIGHT"]["TO"])
    {
        height += SPEED_SIZE;
    }
    else if (height > ANIMATION_MODES[mode]["HEIGHT"]["TO"])
    {
        height -= SPEED_SIZE;
    }
}

// Обновление размера блоков
void refreshBlocksSize(Blocks &blocks, Vector2f &currentSize)
{
    if (currentSize.x != ANIMATION_MODES[mode]["WIDTH"]["TO"] || currentSize.y != ANIMATION_MODES[mode]["HEIGHT"]["TO"])
    {
        for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
        {
            refreshBlockWidth(currentSize.x);
            refreshBlockHeight(currentSize.y);

            blocks.rectangles[i].setPosition(blocks.rectangles[i].getPosition().x,
                                             ((blocks.currentSize.y + RECTANGLE_DISTANCE) * i) + blocks.rectangles[0].getPosition().y);
            blocks.rectangles[i].setSize(currentSize);
        }
    }
}

// Обновление цвета и прозрачности блоков
void refreshBlocksColor(Uint8 &currentColor, const string &colorStr)
{
    if (static_cast<int>(currentColor) < ANIMATION_MODES[mode][colorStr]["TO"])
    {
        currentColor = Uint8(static_cast<int>(currentColor) + SPEED_COLOR);
    }
    else if (static_cast<int>(currentColor) > ANIMATION_MODES[mode][colorStr]["TO"])
    {
        currentColor = Uint8(static_cast<int>(currentColor) - SPEED_COLOR);
    }
}

// Обновление цвета блоков
void refreshBlocksColors(Blocks &blocks)
{
    refreshBlocksColor(blocks.currentRGBA.r, "COLOR_RED");
    refreshBlocksColor(blocks.currentRGBA.g, "COLOR_GREEN");
    refreshBlocksColor(blocks.currentRGBA.b, "COLOR_BLUE");
    refreshBlocksColor(blocks.currentRGBA.a, "OPACITY");
}

// Движение блоков
void moveBlocks(Blocks &blocks)
{
    for (unsigned i = 0; i < RECTANGLE_COUNT; ++i)
    {
        blocks.rectangles[i].setPosition(blocks.rectangles[i].getPosition().x + ANIMATION_MODES[mode]["SPEED"]["X"],
                                         blocks.rectangles[i].getPosition().y + ANIMATION_MODES[mode]["SPEED"]["Y"]);
        blocks.rectangles[i].setFillColor(blocks.currentRGBA);
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

        if (mode != ANIMATION_MODES.size())
        {
            refreshBlocks(blocks);
        }
        if (doesBlocksCollideWithWall(blocks) && (mode + 1 != ANIMATION_MODES.size()))
        {
                mode++;
        }
        update(window, blocks.rectangles);
    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Animation", Style::Close, settings);
    Blocks blocks;
    
    initializeBlocks(blocks);
    
    processAnimation(window, blocks);

    return 0;
}