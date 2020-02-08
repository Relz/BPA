// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_SKILLPANEL_H
#define ULTIMATE_SHAMAN_KING_SKILLPANEL_H

#include "Skill.h"

class CSkillPanel
{
public:
	void Draw(sf::RenderTarget & target, bool isPlayerWithSpirit) const;
	void SetSkills(std::vector<CSkill *> * skills);
	size_t GetSkillCount() const;
	void SetPosition(const sf::Vector2f & position);
	void SetOffsetY(float offsetXs);
	float GetWidth() const;
	float GetHeight() const;
	CSkill * GetSkillByIndex(int skillIndex);

private:
	std::vector<CSkill*> * m_skills;
	sf::Vector2f m_position;

	float m_offsetY = 0;

	float m_width = 0;
	float m_height = 0;
};


#endif //ULTIMATE_SHAMAN_KING_SKILLPANEL_H
