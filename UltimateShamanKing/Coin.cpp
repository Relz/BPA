// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Coin.h"

void CCoin::Init(float value, sf::Vector2f position)
{
	m_value = value;
	m_sprite.setPosition(position);
}

void CCoin::Draw(sf::RenderTarget & target) const
{
	target.draw(m_sprite);
}

void CCoin::SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom)
{
	m_sprite.setTextureRect(sf::IntRect(playerSpriteRect.left, playerSpriteRect.top, playerSpriteRect.width, playerSpriteRect.height));
	SetSprite(spritePath, zoom);
}

void CCoin::SetSprite(const std::string & spritePath, float zoom)
{
	SetTexture(m_texture, spritePath);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(zoom, zoom);
}

void CCoin::Process()
{
	Animate();
}

sf::FloatRect CCoin::GetSpriteRect() const
{
	return m_sprite.getGlobalBounds();
}

float CCoin::GetValue() const
{
	return m_value;
}

void CCoin::SetTexture(sf::Texture & texture, const std::string & texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		throw std::invalid_argument("\"" + texturePath + "\" not found");
	}
}

void CCoin::Animate()
{
	float deltaSec = m_animationClock.getElapsedTime().asSeconds();
	if (deltaSec > 0.1)
	{
		m_currentAnimationSprite = (m_currentAnimationSprite == 9) ? 0 : m_currentAnimationSprite + 1;
		sf::IntRect textureRect = m_sprite.getTextureRect();
		textureRect.left = static_cast<int>(textureRect.width * m_currentAnimationSprite);
		m_sprite.setTextureRect(textureRect);
		m_animationClock.restart();
	}
}
