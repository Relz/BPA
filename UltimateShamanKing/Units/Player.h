// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_PLAYER_H
#define ULTIMATE_SHAMAN_KING_PLAYER_H

#include "Unit.h"

class CPlayer : public CUnit
{
public:
	void MoveProcess(const std::vector<TmxObject> & collisionBlocks) override;
	bool DoesAttack() const;
	void Die() override;

private:
	void UpdateDirection();
	void Animate(sf::Clock & animationClock);
	void UpdateStayingSprite();
	void UpdateMovingSprite();
	void UpdateJumpingSprite();
	void UpdateAttackingSprite();

	sf::Clock m_animationClock;
	size_t m_currentStayingSprite = 0;
	size_t m_currentMovingSprite = 0;
	size_t m_currentAttackingSprite = 0;

	sf::Clock m_attackingClock;

	sf::Vector2f m_lastDirection;
};


#endif //ULTIMATE_SHAMAN_KING_PLAYER_H
