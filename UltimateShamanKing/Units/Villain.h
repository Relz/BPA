// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_VILLAIN_H
#define ULTIMATE_SHAMAN_KING_VILLAIN_H

#include "Unit.h"

class CVillain : public CUnit
{
public:
	void Process(const std::vector<TmxObject> & collisionBlocks) override;
	void UpdateDirection(float playerLeft);

private:
	void Animate(sf::Clock & animationClock);
	void UpdateStayingSprite();

	sf::Clock m_animationClock;
	size_t m_currentStayingSprite = 0;
};


#endif //ULTIMATE_SHAMAN_KING_VILLAIN_H
