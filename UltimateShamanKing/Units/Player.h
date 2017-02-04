// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_PLAYER_H
#define ULTIMATE_SHAMAN_KING_PLAYER_H

#include "Unit.h"

class CPlayer : public CUnit
{
public:
	CPlayer();
	void Init(const std::wstring & name,
			sf::Vector2f startPosition,
			float movementSpeed,
			float upSpeed,
			float downSpeed,
			float gravity,
			float dyingTimeSec,
			size_t HP,
			size_t SP,
			size_t strength);
	void Process(const std::vector<TmxObject> & collisionBlocks) override;
	void Draw(sf::RenderTarget & target) const override;
	void SetPosition(float x, float y) override;
	void SetPosition(const sf::Vector2f & position) override;
	void MoveX() override;
	void Gravity() override;
	void ReduceSP(float value);
	float GetSP() const;

private:
	void UpdateDirection();
	void Animate(sf::Clock & animationClock);
	void UpdateStayingSprite();
	void UpdateMovingSprite();
	void UpdateJumpingSprite();
	void UpdateAttackingSprite();
	bool DoesAttack() const;

	sf::Clock m_animationClock;
	size_t m_currentStayingSprite = 0;
	size_t m_currentMovingSprite = 0;
	size_t m_currentAttackingSprite = 0;

	sf::Clock m_attackingClock;

	CLine m_SPLine;

	float m_SP = 100;

};


#endif //ULTIMATE_SHAMAN_KING_PLAYER_H
