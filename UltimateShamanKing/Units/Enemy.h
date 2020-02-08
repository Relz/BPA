// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_ENEMY_H
#define ULTIMATE_SHAMAN_KING_ENEMY_H

#include "Unit.h"
#include "../Snowball.h"
#include "../Random.h"

class CEnemy : public CUnit
{
public:
	void Init(const std::wstring & name,
	          sf::Vector2f startPosition,
	          float movementSpeed,
	          float upSpeed,
	          float downSpeed,
	          float gravity,
	          float dyingTimeSec,
	          float movingCooldownSec,
	          size_t HP,
	          size_t strength);
	void Process(const std::vector<TmxObject> & collisionBlocks) override;
	void Die() override;
	void CreateNewSnowball(float directionX);
	CSnowball * GetSnowball() const;
	void DestroySnowball();

private:
	void UpdateDirection();
	void Animate(sf::Clock & animationClock);
	void UpdateStayingSprite();
	void UpdateMovingSprite();
	void UpdateJumpingSprite();
	void UpdateDyingSprite();

	sf::Clock m_animationClock;
	sf::Clock m_movingClock;
	sf::Clock m_stayingClock;

	float m_movingCooldownSec = 0;
	size_t m_currentStayingSprite = 0;
	size_t m_currentMovingSprite = 0;
	size_t m_currentDyingSprite = 0;

	float m_stayingTime = (float)(myRandom.GetRandomValue(40, 60)) / 10;

	bool m_justDied = false;

	std::unique_ptr<CSnowball> m_snowball = nullptr;
};

#endif //ULTIMATE_SHAMAN_KING_ENEMY_H
