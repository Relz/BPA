// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Shield.h"

void CShield::Draw(sf::RenderTarget & target, float lastDirectionX)
{
	if (lastDirectionX == 1)
	{
		sf::IntRect textureRect = m_sprite.getTextureRect();
		textureRect.width = m_startWidth;
		textureRect.left = 0;
		m_sprite.setTextureRect(textureRect);
	}
	else if (lastDirectionX == -1)
	{
		sf::IntRect textureRect = m_sprite.getTextureRect();
		textureRect.width = -m_startWidth;
		textureRect.left = m_startWidth;
		m_sprite.setTextureRect(textureRect);
	}
	target.draw(m_sprite);
}

void CShield::SetSprite(const std::string & spritePath, float zoom)
{
	SetTexture(m_texture, spritePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setColor(sf::Color(255, 255, 255, 210));
	m_sprite.setScale(zoom, zoom);
	m_startWidth = static_cast<int>(m_sprite.getGlobalBounds().width);
}

void CShield::SetPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

void CShield::SetTexture(sf::Texture & texture, const std::string & texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		throw std::invalid_argument("\"" + texturePath + "\" not found");
	}
}
