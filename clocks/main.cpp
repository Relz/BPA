#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

using namespace sf;

const int screenWidth = 800;
const int screenHeight = 600;
const int clockCircleThickness = 2;
const int clockCircleSize = 250;
const Color clockCircleColor = Color::Black;
const int clockCirclePointNumber = 100;
const float PI = 3.1415927f;
const int hourDotRadius = 3;
const int aroundHourDotRadius = 1;
const Color dotColor = Color::Black;
const int centerCircleRadius = 10;
const Color centerCircleColor = Color::Red;
const int centerCirclePointNumber = 100;

void initializeClockCircle();

//Инициализация точек окружности часов
void initializeDots(CircleShape *dots)
{
    int x, y;
    float angle = 0.0f;
    for (int i = 0; i < 60; i++)
    {
        x = (int)((clockCircleSize - 10) * cos(angle));
        y = (int)((clockCircleSize - 10) * sin(angle));

        dots[i] = (i % 5 == 0) ? CircleShape(hourDotRadius) : CircleShape(aroundHourDotRadius);
        dots[i].setFillColor(dotColor);
        dots[i].setOrigin(dots[i].getGlobalBounds().width / 2, dots[i].getGlobalBounds().height / 2);
        dots[i].setPosition(x + screenWidth / 2, y + screenHeight / 2);

        angle = angle + ((2 * PI) / 60 );
    }
}

//Инициализация внешней окружности часов
void initializeClockCircle(CircleShape &clockCircle)
{
    clockCircle.setPointCount(clockCirclePointNumber);
    clockCircle.setOutlineThickness(clockCircleThickness);
    clockCircle.setOutlineColor(clockCircleColor);
    clockCircle.setOrigin(clockCircle.getGlobalBounds().width / 2, clockCircle.getGlobalBounds().height / 2);
    clockCircle.setPosition(screenWidth / 2 + clockCircleThickness, screenHeight / 2 + clockCircleThickness);
}

//Инициализцаия цетральной окружности часов
void initializeCenterClockCircle(const Vector2f &windowCenter, CircleShape &centerCircle)
{
    centerCircle.setPointCount(centerCirclePointNumber);
    centerCircle.setFillColor(centerCircleColor);
    centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
    centerCircle.setPosition(windowCenter);
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(screenWidth, screenHeight), "SFML Analog Clock", Style::Close, settings);
    Vector2f windowCenter = Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    CircleShape dots[60];
    initializeDots(dots);

    CircleShape clockCircle(clockCircleSize);
    initializeClockCircle(clockCircle);

    CircleShape centerCircle(centerCircleRadius);
    initializeCenterClockCircle(windowCenter, centerCircle);

    // Create hour, minute, and seconds hands
    RectangleShape hourHand(Vector2f(5, 180));
    RectangleShape minuteHand(Vector2f(3, 240));
    RectangleShape secondsHand(Vector2f(2, 250));

    hourHand.setFillColor(Color::Black);
    minuteHand.setFillColor(Color::Black);
    secondsHand.setFillColor(Color::Red);

    hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
    minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
    secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);

    hourHand.setPosition(windowCenter);
    minuteHand.setPosition(windowCenter);
    secondsHand.setPosition(windowCenter);

    // Create sound effect
    Music clockTick;
    if (!clockTick.openFromFile("resources/clock-1.wav"))
    {
        return 1;
    }
    clockTick.setLoop(true);
    clockTick.play();

    // Use a part of SFML logo as clock brand
    Texture clockBrand;
    if (!clockBrand.loadFromFile("resources/clock-brand.png"))
    {
        return 1;
    }

    Sprite clockBrandSprite;
    clockBrandSprite.setTexture(clockBrand);
    clockBrandSprite.setOrigin(clockBrandSprite.getTextureRect().left + clockBrandSprite.getTextureRect().width/2.0f,
                               clockBrandSprite.getTextureRect().top + clockBrandSprite.getTextureRect().height/2.0f);

    clockBrandSprite.setPosition(window.getSize().x/2, window.getSize().y -100);


    // Create clock background
    Texture clockImage;
    if (!clockImage.loadFromFile("resources/clock-image.png"))
    {
        return 1;
    }

    clockCircle.setTexture(&clockImage);
    clockCircle.setTextureRect(IntRect(40, 0, 500, 500));

    while (window.isOpen())
    {
        // Handle events
        Event event;
        while (window.pollEvent(event))
        {
            // Window closed: exit
            if (event.type == Event::Closed)
                window.close();
        }

        // Get system time
        std::time_t currentTime = std::time(NULL);

        struct tm * ptm = localtime(&currentTime);

        hourHand.setRotation(ptm->tm_hour*30 + (ptm->tm_min/2) );
        minuteHand.setRotation(ptm->tm_min*6 + (ptm->tm_sec/12) );
        secondsHand.setRotation(ptm->tm_sec*6);

        window.clear(Color::White);
        window.draw(clockCircle);

        for (int i=0; i<60; i++)
        {
            window.draw(dots[i]);
        }

        window.draw(clockBrandSprite);
        window.draw(hourHand);
        window.draw(minuteHand);
        window.draw(secondsHand);
        window.draw(centerCircle);

        window.display();
    }

    return 0;
}