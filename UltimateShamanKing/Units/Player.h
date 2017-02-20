// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_PLAYER_H
#define ULTIMATE_SHAMAN_KING_PLAYER_H

#include "Unit.h"
#include "../Shield.h"

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
			size_t strength,
			size_t skillCount);
	void Process(const std::vector<TmxObject> & collisionBlocks) override;
	void Draw(sf::RenderTarget & target);
	void SetPosition(float x, float y) override;
	void SetPosition(const sf::Vector2f & position) override;
	void MoveX() override;
	void Gravity() override;
	void ReduceSP(float value);
	void IncreaseSP(float value);
	float GetSP() const;
	int GetUsingSkill() const;
	void SetSpirit(bool isWithSpirit);
	void SetShield(bool isWithShield);
	bool IsWithSpirit() const;
	bool IsUsingCloudstrike() const;
	bool IsWithShield() const;
	void UseSkill(const std::string skillName, float spReduce);
	float GetMoney() const;
	void IncreaseMoney(float value);

private:
	void UpdateDirection();
	void UpdateSkillUsing();
	void Animate(sf::Clock & animationClock);
	void UpdateStayingSprite();
	void UpdateMovingSprite();
	void UpdateJumpingSprite();
	void UpdateAttackingSprite();
	void UpdateUsingCloudstrikeSprite();
	bool DoesAttack() const;
	size_t GetSkillCount() const;
	void SetUsingCloudstrike(bool value);

	sf::Clock m_animationClock;
	size_t m_currentStayingSprite = 0;
	size_t m_currentMovingSprite = 0;
	size_t m_currentAttackingSprite = 0;
	size_t m_currentUsingCloudstrikeSprite = 0;

	sf::Clock m_attackingClock;
	sf::Clock m_usingCloudstrikeClock;

	sf::Clock m_spReducingForSpiritClock;
	sf::Clock m_spReducingForShieldClock;

	CLine m_SPLine;

	float m_SP = 100;
	size_t m_skillCount = 0;
	int m_usingSkill = -1;

	bool m_isWithSpirit = false;
	bool m_isUsingCloudstrike = false;
	bool m_isWithShield = false;

	CShield m_shield;

	float m_money = 0;

};


#endif //ULTIMATE_SHAMAN_KING_PLAYER_H
