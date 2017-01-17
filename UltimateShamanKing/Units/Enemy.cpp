// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Enemy.h"

void CEnemy::Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity, size_t movingCooldownSec)
{
    CUnit::Init(startPosition, movementSpeed, upSpeed, downSpeed, gravity);
    m_movingCooldownSec = movingCooldownSec;
    if (!m_snowBallTextrure.loadFromFile("../res/Images/Sprites/snowball.png"))
    {
        throw std::invalid_argument(std::string("\"") + "../res/Images/Sprites/snowball.png" + "\" not found");
    }
    m_snowBall.setTexture(m_snowBallTextrure);
}

void CEnemy::MoveProcess(const std::vector<TmxObject> & collisionBlocks)
{
    float deltaSec = m_animationClock.getElapsedTime().asSeconds();
    UpdateDirection();
    Animate(m_animationClock);
    UpdateCollision(collisionBlocks);
    if ((direction.x > 0 && !collision.right) || (direction.x < 0 && !collision.left))
    {
        MoveX();
    }
    if (IsStaying() && m_stayingClock.getElapsedTime().asSeconds() > 5)
    {
        direction.x = (m_random.getRandomValue(0, 1) == 0) ? -1 : 1;
        m_movingClock.restart();
    }
    if (collision.left || collision.right)
    {
        direction.x = -direction.x;
    }
    if (collision.top)
    {
        downSpeed = 0;
    }
    if (collision.bottom)
    {
        downSpeed = startDownSpeed;
        jumping = false;
    }
    else
    {
        jumping = true;
        downSpeed += gravity;
        Gravity();
    }
}

void CEnemy::UpdateDirection()
{
    if (m_movingClock.getElapsedTime().asSeconds() >= m_movingCooldownSec && !IsStaying())
    {
        direction.x = 0;
        m_stayingClock.restart();
    }
    if (direction.x == 1 || direction.x == -1)
    {
        m_lastDirection.x = direction.x;
    }
}

void CEnemy::Animate(sf::Clock & animationClock)
{
    float deltaSec = animationClock.getElapsedTime().asSeconds();
    if (deltaSec > 0.1)
    {
        if (!jumping)
        {
            if (!IsStaying())
            {
                UpdateMovingSprite();
                animationClock.restart();
            }
        }
        else
        {
            UpdateJumpingSprite();
        }
    }
    if (deltaSec > 0.3)
    {
        if (!jumping && IsStaying())
        {
            UpdateStayingSprite();
        }
        animationClock.restart();
    }
}


void CEnemy::UpdateStayingSprite()
{
    m_currentMovingSprite = 0;
    m_currentStayingSprite = (m_currentStayingSprite == 2) ? 0 : m_currentStayingSprite + 1;
    sf::IntRect textureRect = m_sprite.getTextureRect();
    int offsetLeft = 0;
    textureRect.top = m_startOffsetTop;
    textureRect.width = abs(textureRect.width);
    if (m_lastDirection.x == -1)
    {
        offsetLeft = textureRect.width;
        textureRect.width = -textureRect.width;
    }

    switch (m_currentStayingSprite)
    {
        case 0:
            textureRect.height = m_startHeight;
            textureRect.left = offsetLeft + 0;
            break;
        case 1:
            textureRect.height = m_startHeight;
            textureRect.left = offsetLeft + 27;
            break;
        case 2:
            textureRect.height = m_startHeight;
            textureRect.left = offsetLeft + 54;
            break;
        default:
            break;
    }
    m_sprite.setTextureRect(textureRect);
}

void CEnemy::UpdateMovingSprite()
{
    m_currentStayingSprite = 0;
    m_currentMovingSprite = (m_currentMovingSprite == 5) ? 0 : m_currentMovingSprite + 1;
    sf::IntRect textureRect = m_sprite.getTextureRect();
    int offsetLeft = 0;
    textureRect.height = m_startHeight;
    textureRect.top = 52;
    textureRect.width = abs(textureRect.width);
    if (m_lastDirection.x == 1)
    {
        offsetLeft = textureRect.width;
        textureRect.width = -textureRect.width;
    }
    switch (m_currentMovingSprite)
    {
        case 0:
            textureRect.left = offsetLeft + 1;
            break;
        case 1:
            textureRect.left = offsetLeft + 33;
            break;
        case 2:
            textureRect.left = offsetLeft + 63;
            break;
        case 3:
            textureRect.left = offsetLeft + 94;
            break;
        case 4:
            textureRect.left = offsetLeft + 126;
            break;
        case 5:
            textureRect.left = offsetLeft + 165;
            break;
        default:
            break;
    }
    m_sprite.setTextureRect(textureRect);
}

void CEnemy::UpdateJumpingSprite()
{
    m_currentStayingSprite = 0;
    m_currentMovingSprite = 0;
    sf::IntRect textureRect = m_sprite.getTextureRect();
    int offsetLeft = 0;
    textureRect.height = m_startHeight;
    textureRect.top = 218;
    textureRect.width = abs(textureRect.width);
    if (m_lastDirection.x == -1)
    {
        offsetLeft = textureRect.width;
        textureRect.width = -textureRect.width;
    }

    textureRect.left = (downSpeed > 0) ? offsetLeft + 20 : offsetLeft + 40;
    m_sprite.setTextureRect(textureRect);
}

void CEnemy::Die()
{

}