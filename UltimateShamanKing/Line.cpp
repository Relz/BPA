// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Line.h"

CLine::CLine(const sf::Color & color)
{
	m_outline.setOutlineThickness(2);
	m_outline.setOutlineColor(sf::Color::Black);
	m_points.setFillColor(color);
	m_outline.setSize(sf::Vector2f(100, 10));
	m_points.setOrigin(50, 0);
	m_outline.setOrigin(50, 0);
}

void CLine::SetPosition(const sf::Vector2f & position)
{
	m_outline.setPosition(position);
	m_points.setPosition(position);
}

void CLine::SetPosition(float x, float y)
{
	m_outline.setPosition(x, y);
	m_points.setPosition(x, y);
}

void CLine::Move(float x, float y)
{
	m_outline.move(x, y);
	m_points.move(x, y);
}

void CLine::SetPoints(float value)
{
	m_points.setSize(sf::Vector2f(value, 10));
}

void CLine::Draw(sf::RenderTarget & target) const
{
	target.draw(m_outline);
	target.draw(m_points);
}