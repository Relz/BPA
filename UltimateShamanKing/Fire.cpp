// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Fire.h"

void CFire::SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom)
{
	if (!m_texture.loadFromFile(spritePath))
	{
		throw std::invalid_argument("\"" + spritePath + "\" not found");
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(playerSpriteRect.left, playerSpriteRect.top, playerSpriteRect.width, playerSpriteRect.height));
	m_sprite.setScale(zoom, zoom);
}

void CFire::SetPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

void CFire::Show()
{
	m_livingTimeClock.restart();
	m_visible = true;
}

void CFire::Process()
{
	if (IsVisible())
	{
		float deltaSec = m_animationClock.getElapsedTime().asSeconds();
		if (deltaSec > 0.1)
		{
			UpdateSprite();
			m_animationClock.restart();
		}
		if (m_livingTimeClock.getElapsedTime().asSeconds() > m_maxLivingTimeSec)
		{
			m_visible = false;
		}
	}
}

void CFire::Draw(sf::RenderTarget & target) const
{
	if (IsVisible())
	{
		target.draw(m_sprite);
	}
}

void CFire::UpdateSprite()
{
	m_currentSprite = (m_currentSprite == 3) ? 0 : m_currentSprite + 1;
	sf::IntRect textureRect = m_sprite.getTextureRect();
	switch (m_currentSprite)
	{
		case 0:
			textureRect.left = 0;
			break;
		case 1:
			textureRect.left = 256;
			break;
		case 2:
			textureRect.left = 512;
			break;
		case 3:
			textureRect.left = 768;
			break;
		default:
			break;
	}
	m_sprite.setTextureRect(textureRect);
}

bool CFire::IsVisible() const
{
	return m_visible;
}
