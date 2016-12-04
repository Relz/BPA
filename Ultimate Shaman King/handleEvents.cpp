#include "stdafx.h"
#include "handleEvents.h"

// Обработка событий на форме
void handleEvents(sf::RenderWindow &window, CYoh &yoh)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    yoh.up = true;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    yoh.right = true;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    yoh.down = true;
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    yoh.left = true;
                }
                break;
            }
            case sf::Event::KeyReleased:
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    yoh.up = false;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    yoh.right = false;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    yoh.down = false;
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    yoh.left = false;
                }
                break;
            }
            default:
                break;
        }
    }
}