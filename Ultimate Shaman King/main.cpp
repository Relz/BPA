#include "stdafx.h"
#include "handleEvents.h"
#include "Yoh.h"
#include "Level.h"

using namespace sf;

// Отрисовка объектов на форме
void drawObjects(RenderWindow &window, b2World & world, Object & player, Level & level)
{
    level.Draw(window);
    for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        if (BodyIterator->GetType() == b2_dynamicBody)
        {
            player.sprite.setPosition(30.f * BodyIterator->GetPosition().x, 1 * BodyIterator->GetPosition().y);
            window.draw(player.sprite);
            std::cout << player.sprite.getPosition().x << " " << player.sprite.getPosition().y << "\n";
        }
    }
    window.display();
}

// Отрисовка формы
void render(RenderWindow &window, b2World & world, Object & player, Level & level)
{
    drawObjects(window, world, player, level);
    window.clear(BACKGROUND_COLOR);
}

// Игровой цикл
void gameLoop(RenderWindow &window, b2World & world, Object & player, b2Body **playerBody, Level & level)
{
    while (window.isOpen())
    {
        handleEvents(window, playerBody);
        render(window, world, player, level);
        world.Step(1.0f / 60.0f, 1, 1);

    }
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    RenderWindow window(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), WINDOW_TITLE, Style::Close, settings);
    window.setFramerateLimit(FPS);


    Level level;
    level.LoadFromFile("level1.tmx");

    b2Vec2 gravity(0.f, 50.f);
    b2World world(gravity);
    sf::Vector2i tileSize = level.GetTileSize();

    level.InitTiles(level, world);

    Object player = level.GetObject("player");
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(player.rect.left, player.rect.top);
    bodyDef.fixedRotation = true;
    b2Body* playerBody = world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(player.rect.width / 2, player.rect.height / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    playerBody->CreateFixture(&fixtureDef);


    gameLoop(window, world, player, &playerBody, level);

    return 0;
}