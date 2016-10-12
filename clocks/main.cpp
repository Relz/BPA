#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

using namespace sf;
using namespace std;

const float PI = 3.1415927f;

const unsigned ANTIALIASING_LEVEL = 8;
const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;

const unsigned CLOCK_CIRCLE_THICKNESS = 2;
const unsigned CLOCK_CIRCLE_SIZE = 250;
const unsigned CLOCK_CIRCLE_POINT_NUMBER = 100;

const unsigned HOUR_DASH_WIDTH = 4;
const unsigned HOUR_DASH_HEIGHT = 20;
const unsigned AROUND_HOUR_DASH_WIDTH = 2;
const unsigned AROUND_HOUR_DASH_HEIGHT = 10;

const unsigned CLOCK_CENTER_CIRCLE_RADIUS = 10;
const unsigned CLOCK_CENTER_POINT_NUMBER = 100;

const unsigned DOT_COUNT = 60;
const unsigned NUMBER_COUNT = 12;

const unsigned HOUR_HAND_WIDTH = 5;
const unsigned MINUTE_HAND_WIDTH = 3;
const unsigned SECOND_HAND_WIDTH = 2;

const unsigned HOUR_HAND_HEIGHT = 180;
const unsigned MINUTE_HAND_HEIGHT = 240;
const unsigned SECOND_HAND_HEIGHT = 250;

const Color DARK_BLUE = Color(0, 0, 60);

const unsigned NUMBER_CIRCLE_RADIUS = 22;
const Color NUMBER_CIRCLE_COLOR = Color(255, 255, 255, 50);

struct ClockFace
{
    Texture backgroundImage;
    RectangleShape dashes[DOT_COUNT];
    Text numbers[NUMBER_COUNT];
    Font numbersFont;
    CircleShape numbersCircles[NUMBER_COUNT];
    CircleShape clockCircle;
    CircleShape centerCircle;
};

struct ClockHands
{
    RectangleShape hourHand;
    RectangleShape minuteHand;
    RectangleShape secondHand;
};

struct MyClock
{
    ClockFace clockFace;
    ClockHands clockHands;
    Music clockTick;
};

struct Point
{
    unsigned x;
    unsigned y;
};

// Получение текщей времени
struct tm *getCurrentTime()
{
    std::time_t currentTime = std::time(NULL);
    return localtime(&currentTime);
}

// Инициализация круга числа
void initializeNumberCircle(ClockFace &clockFace, unsigned number, float posX, float posY)
{
    clockFace.numbersCircles[number].setRadius(NUMBER_CIRCLE_RADIUS);
    clockFace.numbersCircles[number].setPointCount(CLOCK_CIRCLE_POINT_NUMBER);
    clockFace.numbersCircles[number].setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
    clockFace.numbersCircles[number].setOutlineColor(DARK_BLUE);
    clockFace.numbersCircles[number].setFillColor(NUMBER_CIRCLE_COLOR);
    clockFace.numbersCircles[number].setOrigin(clockFace.numbersCircles[number].getGlobalBounds().width / 2, clockFace.numbersCircles[number].getGlobalBounds().height / 2);
    clockFace.numbersCircles[number].setPosition(posX, posY);
}

// Инициализация числа
void initializeNumber(ClockFace &clockFace, unsigned number, float angle, Vector2f &windowCenter)
{
    clockFace.numbers[number].setFont(clockFace.numbersFont);
    clockFace.numbers[number].setFillColor(DARK_BLUE);
    clockFace.numbers[number].setCharacterSize(35);
    clockFace.numbers[number].setString(to_string(number + 1));
    Vector2f numberPosition = Vector2f((CLOCK_CIRCLE_SIZE - 50) * cos(angle + PI / 6), (CLOCK_CIRCLE_SIZE - 50) * sin(angle + PI / 6));
    Vector2f positionText(numberPosition + windowCenter);
    clockFace.numbers[number].setPosition(positionText.x, positionText.y - clockFace.numbers[number].getGlobalBounds().height / 2.0f);
    clockFace.numbers[number].setOrigin(clockFace.numbers[number].getGlobalBounds().width / 2.0f, clockFace.numbers[number].getGlobalBounds().height / 2.0f);
    initializeNumberCircle(clockFace, number,
                       clockFace.numbers[number].getGlobalBounds().left + clockFace.numbers[number].getGlobalBounds().width / 2.0f + 3,
                       clockFace.numbers[number].getGlobalBounds().top + clockFace.numbers[number].getGlobalBounds().height / 2.0f + 3);
}

// Инициализация точки окружности и числа
void initializeDashAndNumber(ClockFace &clockFace, unsigned i, float angle, Point &coors, Vector2f &windowCenter)
{
    if (i % 5 == 0)
    {
        clockFace.dashes[i] = RectangleShape(Vector2f(HOUR_DASH_WIDTH, HOUR_DASH_HEIGHT));
        initializeNumber(clockFace, i / 5, angle, windowCenter);
    }
    else
    {
        clockFace.dashes[i] = RectangleShape(Vector2f(AROUND_HOUR_DASH_WIDTH, AROUND_HOUR_DASH_HEIGHT));
    }
    clockFace.dashes[i].setFillColor(DARK_BLUE);
    clockFace.dashes[i].setOrigin(clockFace.dashes[i].getGlobalBounds().width / 2, clockFace.dashes[i].getGlobalBounds().height / 2);
    clockFace.dashes[i].setPosition(coors.x + SCREEN_WIDTH / 2, coors.y + SCREEN_HEIGHT / 2);
    clockFace.dashes[i].setRotation(angle * 180 / PI + 90);
}

// Инициализация точек окружности часов и чисел
bool initializeDashesAndNumbers(ClockFace &clockFace, Vector2f &windowCenter)
{
    Point coors;
    float angle = 1.5f * PI;
    for (unsigned i = 0; i < 60; i++)
    {
        coors.x = (unsigned)((CLOCK_CIRCLE_SIZE - 10) * cos(angle));
        coors.y = (unsigned)((CLOCK_CIRCLE_SIZE - 10) * sin(angle));
        initializeDashAndNumber(clockFace, i, angle, coors, windowCenter);
        angle = angle + ((2 * PI) / 60);
    }
    return true;
}

// Инициализация фонового изображения часов
void initializeClockImage(CircleShape &clockCircle, Texture &clockImage)
{
    clockCircle.setTexture(&clockImage);
    clockCircle.setTextureRect(IntRect(40, 0, 500, 500));
}

// Инициализация внешней окружности часов
bool initializeClockCircle(CircleShape &clockCircle)
{
    clockCircle.setRadius(CLOCK_CIRCLE_SIZE);
    clockCircle.setPointCount(CLOCK_CIRCLE_POINT_NUMBER);
    clockCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
    clockCircle.setOutlineColor(Color::Black);
    clockCircle.setOrigin(clockCircle.getGlobalBounds().width / 2, clockCircle.getGlobalBounds().height / 2);
    clockCircle.setPosition(SCREEN_WIDTH / 2 + CLOCK_CIRCLE_THICKNESS, SCREEN_HEIGHT / 2 + CLOCK_CIRCLE_THICKNESS);
    return true;
}

// Инициализцаия цетральной окружности часов
void initializeCenterClockCircle(const Vector2f &windowCenter, CircleShape &centerCircle)
{
    centerCircle.setRadius(CLOCK_CENTER_CIRCLE_RADIUS);
    centerCircle.setPointCount(CLOCK_CENTER_POINT_NUMBER);
    centerCircle.setFillColor(Color::Red);
    centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
    centerCircle.setPosition(windowCenter);
}

// Инициализация циферблата часов
bool initializeClockFace(ClockFace &clockFace, Vector2f &windowCenter)
{
    if (!clockFace.numbersFont.loadFromFile("resources/DroidSans-Bold.ttf")
        || !initializeClockCircle(clockFace.clockCircle)
        || !clockFace.backgroundImage.loadFromFile("resources/background.png"))
    {
        return false;
    }
    initializeClockImage(clockFace.clockCircle, clockFace.backgroundImage);
    initializeDashesAndNumbers(clockFace, windowCenter);
    initializeCenterClockCircle(windowCenter, clockFace.centerCircle);
    return true;
}

// Инициализация стрелок времени
void initializeHands(ClockHands &clockHands, Vector2f &windowCenter)
{
    clockHands.hourHand.setSize(Vector2f(HOUR_HAND_WIDTH, HOUR_HAND_HEIGHT));
    clockHands.minuteHand.setSize(Vector2f(MINUTE_HAND_WIDTH, MINUTE_HAND_HEIGHT));
    clockHands.secondHand.setSize(Vector2f(SECOND_HAND_WIDTH, SECOND_HAND_HEIGHT));

    clockHands.hourHand.setFillColor(Color::Black);
    clockHands.minuteHand.setFillColor(Color::Black);
    clockHands.secondHand.setFillColor(Color::Red);

    clockHands.hourHand.setOrigin(clockHands.hourHand.getGlobalBounds().width / 2, clockHands.hourHand.getGlobalBounds().height - 25);
    clockHands.minuteHand.setOrigin(clockHands.minuteHand.getGlobalBounds().width / 2, clockHands.minuteHand.getGlobalBounds().height - 25);
    clockHands.secondHand.setOrigin(clockHands.secondHand.getGlobalBounds().width / 2, clockHands.secondHand.getGlobalBounds().height - 25);

    clockHands.hourHand.setPosition(windowCenter);
    clockHands.minuteHand.setPosition(windowCenter);
    clockHands.secondHand.setPosition(windowCenter);
}

// Инициализация звука тиканья
void initializeClockTick(Music &clockTick)
{
    clockTick.setLoop(true);
    clockTick.play();
}

// Инициализация часов
bool initializeClock(MyClock &clock, Vector2f &windowCenter)
{
    if (!initializeClockFace(clock.clockFace, windowCenter) ||
        !clock.clockTick.openFromFile("resources/clock-1.wav"))
    {
        return false;
    }

    initializeClockTick(clock.clockTick);
    initializeHands(clock.clockHands, windowCenter);
    return true;
}

// Отрисовка засечек и чисел
void drawDashesAndNumbers(RenderWindow &window, RectangleShape *dashes, Text *numbers, CircleShape *numbersCircles)
{
    struct tm * ptm = getCurrentTime();
    for (int i = 0; i < DOT_COUNT; i++)
    {
        dashes[i].setFillColor((i == ptm->tm_sec) ? Color::Red : DARK_BLUE);
        window.draw(dashes[i]);
        if (i % 5 == 0)
        {
            window.draw(numbersCircles[i / 5]);
            window.draw(numbers[i / 5]);
        }
    }
}

// Отрисовка циферблата часов
void drawClockFace(RenderWindow &window, ClockFace &clockFace)
{
    window.draw(clockFace.clockCircle);
    drawDashesAndNumbers(window, clockFace.dashes, clockFace.numbers, clockFace.numbersCircles);
}

// Отрисовка стрелок времени
void drawClockHands(RenderWindow &window, ClockHands &clockHands)
{
    window.draw(clockHands.hourHand);
    window.draw(clockHands.minuteHand);
    window.draw(clockHands.secondHand);
}

// Отрисовка объектов на форме
void drawObjects(RenderWindow &window, MyClock &clock)
{
    drawClockFace(window, clock.clockFace);
    drawClockHands(window, clock.clockHands);
    window.draw(clock.clockFace.centerCircle);
    window.display();
}

// Обновление Формы
void update(RenderWindow &window, MyClock &clock)
{
    window.clear(Color::White);
    drawObjects(window, clock);
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

// Обновление стрелок времени
void refreshHandsRotations(ClockHands &clockHands)
{
    struct tm * ptm = getCurrentTime();
    clockHands.hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
    clockHands.minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
    clockHands.secondHand.setRotation(ptm->tm_sec * 6);
}

// Игровой цикл
void processClock(RenderWindow &window, MyClock &clock)
{
    while (window.isOpen())
    {
        handleEvents(window);

        refreshHandsRotations(clock.clockHands);
        update(window, clock);
    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;

    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Analog Clock", Style::Close, settings);
    Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    MyClock clock;
    if (!initializeClock(clock, windowCenter))
    {
        return 1;
    }

    processClock(window, clock);

    return 0;
}