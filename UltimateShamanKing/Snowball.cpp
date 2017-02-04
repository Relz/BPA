// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Snowball.h"

void CSnowball::Init(sf::Vector2f startPosition, float directionX, float speed, float maxLivingTimeSec, float strength)
{
	m_sprite.setPosition(startPosition);
	this->m_directionX = directionX;
	this->m_speed = speed;
	this->m_maxLivingTimeSec = maxLivingTimeSec;
	this->m_strength = strength;
	m_livingClock.restart();
}

void CSnowball::SetImage(const std::string & imagePath, float zoom)
{
	if (!m_texture.loadFromFile(imagePath))
	{
		throw std::invalid_argument("\"" + imagePath + "\" not found");
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(zoom, zoom);
}

void CSnowball::Draw(sf::RenderTarget & target) const
{
	if (IsVisible())
	{
		target.draw(m_sprite);
	}
}

void CSnowball::Process()
{
	m_sprite.move(m_directionX * m_speed, 0);
}

void CSnowball::Hide()
{
	m_visible = false;
}

float CSnowball::GetLivingTimeSec() const
{
	return m_livingClock.getElapsedTime().asSeconds();
}

float CSnowball::GetMaxLivingTimeSec() const
{
	return m_maxLivingTimeSec;
}

sf::FloatRect CSnowball::GetTextureFloatRect() const
{
	return sf::FloatRect(m_sprite.getPosition().x, m_sprite.getPosition().y, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}

float CSnowball::GetStrength() const
{
	return m_strength;
}

bool CSnowball::IsVisible() const
{
	return m_visible;
}

float CSnowball::GetDirectionX() const
{
	return m_directionX;
}
