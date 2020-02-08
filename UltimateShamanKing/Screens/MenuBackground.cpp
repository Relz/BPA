// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "MenuBackground.h"

void CMenuBackground::SetSprite(const std::string & imagePath, const sf::Vector2u & windowSize)
{
	if (!m_texture.loadFromFile(imagePath))
	{
		throw std::invalid_argument("Failed to load \"" + imagePath + "\"");
	}
	m_sprite.setTexture(m_texture);
	float scale = windowSize.x / m_sprite.getGlobalBounds().width;
	m_sprite.setScale(scale, scale);
}

void CMenuBackground::SetMenuPosition(const sf::Vector2f & menuPosition)
{
	m_menuPosition = menuPosition;
}

void CMenuBackground::Draw(sf::RenderTarget & target) const
{
	target.draw(m_sprite);
}

sf::Vector2f CMenuBackground::GetMenuPosition() const
{
	return m_menuPosition;
}

void CMenuBackground::SetTransparent(sf::Uint8 value)
{
	m_sprite.setColor(sf::Color(255, 255, 255, value));
}
