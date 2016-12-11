#include "stdafx.h"
#include "handleEvents.h"

// Обработка событий на форме
void handleEvents(sf::RenderWindow &window, b2Body **Body)
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
                if(event.key.code == sf::Keyboard::W)
                    //(*Body)->SetLinearVelocity(b2Vec2(0.0f, -50.0f));
                    (*Body)->ApplyLinearImpulse(b2Vec2(0.0f, -50.0f), b2Vec2(0.0f, 0.0f), true  );

                if(event.key.code == sf::Keyboard::D)
                    (*Body)->SetLinearVelocity(b2Vec2(5.0f, 0.0f));

                if(event.key.code == sf::Keyboard::A)
                    (*Body)->SetLinearVelocity(b2Vec2(-5.0f, 0.0f));
                break;
            }
            default:
                break;
        }
    }
}