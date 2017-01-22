#include "stdafx.h"
#include "HPLine.h"

CHPLine::CHPLine()
{
	m_outline.setOutlineThickness(2);
	m_outline.setOutlineColor(sf::Color::Black);
	m_hp.setFillColor(sf::Color::Red);
	m_outline.setSize(sf::Vector2f(100, 10));
}

void CHPLine::SetPosition(const sf::Vector2f & position)
{
	m_outline.setPosition(position);
	m_hp.setPosition(position);
}

void CHPLine::SetPosition(float x, float y)
{
	m_outline.setPosition(x, y);
	m_hp.setPosition(x, y);
}

void CHPLine::Move(float x, float y)
{
	m_outline.move(x, y);
	m_hp.move(x, y);
}

void CHPLine::SetHP(float value)
{
	m_hp.setSize(sf::Vector2f(value, 10));
}

void CHPLine::Draw(sf::RenderTarget & target) const
{
	target.draw(m_outline);
	target.draw(m_hp);
}