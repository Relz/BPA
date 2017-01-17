// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_ENEMY_H
#define ULTIMATE_SHAMAN_KING_ENEMY_H

#include "Unit.h"

struct Random
{
    std::random_device randomDevice;
    std::mt19937 gen;

    size_t getRandomValue(size_t min, size_t max)
    {
        gen.seed(randomDevice());
        std::uniform_int_distribution<size_t> dist(min, max);
        return dist(gen);
    }
};

class CEnemy : public CUnit
{
public:
    void Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity, size_t movingCooldownSec);
    void MoveProcess(const std::vector<TmxObject> & collisionBlocks) override;
    void Die();

private:
    void UpdateDirection();
    void Animate(sf::Clock & animationClock);
    void UpdateStayingSprite();
    void UpdateMovingSprite();
    void UpdateJumpingSprite();

    sf::Clock m_animationClock;
    sf::Clock m_movingClock;
    sf::Clock m_stayingClock;
    size_t m_movingCooldownSec = 0;
    size_t m_currentStayingSprite = 0;
    size_t m_currentMovingSprite = 0;

    sf::Texture m_snowBallTextrure;
    sf::Sprite m_snowBall;

    sf::Vector2f m_lastDirection;

    Random m_random;
};


#endif //ULTIMATE_SHAMAN_KING_ENEMY_H
