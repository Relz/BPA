// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Skill.h"

CSkill::CSkill(const std::string & iconPath, const std::string & name, float size, bool isCanBeUsedOnlyWithSpirit, float spReduce)
{
	if (!m_image.loadFromFile(iconPath))
	{
		throw std::invalid_argument("\"" + iconPath + "\" not found");
	}
	if (!m_texture.loadFromFile(iconPath))
	{
		throw std::invalid_argument("\"" + iconPath + "\" not found");
	}
	m_sprite.setTexture(m_texture);
	m_name = name;
	m_isCanBeUsedOnlyWithSpirit = isCanBeUsedOnlyWithSpirit;
	m_sprite.setScale(size / m_sprite.getGlobalBounds().width, size / m_sprite.getGlobalBounds().height);
	m_spReduce = spReduce;
}

void CSkill::Draw(sf::RenderTarget & target) const
{
	target.draw(m_sprite);
}

void CSkill::SetPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

float CSkill::GetSize() const
{
	return m_sprite.getGlobalBounds().width;
}

std::string CSkill::GetName() const
{
	return m_name;
}

bool CSkill::IsCanBeUsedOnlyWithSpirit() const
{
	return m_isCanBeUsedOnlyWithSpirit;
}

void CSkill::SetMonochrome(bool monochrome)
{
	if (monochrome)
	{
		m_sprite.setColor(sf::Color(255, 255, 255, 128));
	}
	else
	{
		m_sprite.setColor(sf::Color(255, 255, 255, 255));
	}
}

float CSkill::GetSpReduce() const
{
	return m_spReduce;
}
