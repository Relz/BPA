// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "SkillPanel.h"

void CSkillPanel::Draw(sf::RenderTarget & target, bool isPlayerWithSpirit) const
{
	size_t i = 0;
	for (CSkill * skill : *m_skills)
	{
		sf::Vector2f position = m_position;
		position.y += (i * (skill->GetSize() + m_offsetY));
		skill->SetPosition(position);
		skill->SetMonochrome(!isPlayerWithSpirit && skill->IsCanBeUsedOnlyWithSpirit());
		skill->Draw(target);
		i++;
	}
}

void CSkillPanel::SetSkills(std::vector<CSkill *> * skills)
{
	m_skills = skills;
	if (!skills->empty())
	{
		m_width = (*(skills->begin()))->GetSize();
		m_height = skills->size() * ((*(skills->begin()))->GetSize() + m_offsetY);
	}
	else
	{
		m_width = 0;
		m_height = 0;
	}
}

size_t CSkillPanel::GetSkillCount() const
{
	return m_skills->size();
}

void CSkillPanel::SetPosition(const sf::Vector2f & position)
{
	m_position = position;
}

void CSkillPanel::SetOffsetY(float offsetY)
{
	m_offsetY = offsetY;
}

float CSkillPanel::GetWidth() const
{
	return m_width;
}

float CSkillPanel::GetHeight() const
{
	return m_height;
}

CSkill * CSkillPanel::GetSkillByIndex(int skillIndex)
{
	CSkill * result = nullptr;
	if (skillIndex >= 0 && skillIndex < static_cast<int>(m_skills->size()))
	{
		result = m_skills->at(skillIndex);
	}
	return result;
}
