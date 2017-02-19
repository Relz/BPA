// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "GameOverView.h"

CGameOverView::CGameOverView()
{
	InitBackground("../res/Images/Game Over.png");
	InitText("Game Over", "../res/Fonts/Wizards Magic.ttf");
	InitSubText("Press Enter to continue", "../res/Fonts/arial.ttf");
}

void CGameOverView::Draw(sf::RenderTarget & target)
{
	m_background.setPosition(m_windowCenter.x - m_windowSize.x / 2, m_windowCenter.y - m_windowSize.y / 2);
	m_text.setPosition(m_windowCenter.x - (m_text.getGlobalBounds().width / 2),
	                 m_windowCenter.y - m_text.getGlobalBounds().height);
	m_subText.setPosition(m_windowCenter.x - (m_subText.getGlobalBounds().width / 2),
	                    m_windowSize.y - (m_subText.getGlobalBounds().height * 2));
	target.draw(m_background);
	target.draw(m_text);
	target.draw(m_subText);
}

void CGameOverView::SetWindowCenter(const sf::Vector2f & windowCenter)
{
	m_windowCenter = windowCenter;
}

void CGameOverView::SetWindowSize(const sf::Vector2u & windowSize)
{
	m_windowSize = windowSize;
}

void CGameOverView::SetBackgroundScale(float x, float y)
{
	m_background.setScale(x, y);
}

float CGameOverView::GetBackgroundWidth() const
{
	return m_background.getLocalBounds().width;
}

void CGameOverView::InitBackground(const std::string & imagePath)
{
	if (!m_backgroundTexture.loadFromFile(imagePath))
	{
		throw std::invalid_argument("Failed to load \"" + imagePath + "\"");
	}
	m_background.setTexture(m_backgroundTexture);
}

void CGameOverView::InitTextFont(const std::string &fontPath)
{
	if (!m_textFont.loadFromFile(fontPath))
	{
		throw std::invalid_argument("Failed to load \"" + fontPath + "\"");
	}
}

void CGameOverView::InitSubTextFont(const std::string &fontPath)
{
	if (!m_subTextFont.loadFromFile(fontPath))
	{
		throw std::invalid_argument("Failed to load \"" + fontPath + "\"");
	}
}

void CGameOverView::InitText(const std::string & textMessage, const std::string & fontPath)
{
	InitTextFont(fontPath);
	m_text.setFont(m_textFont);
	m_text.setString(textMessage);
	m_text.setFillColor(sf::Color(200, 0, 0));
	m_text.setOutlineThickness(5);
	m_text.setOutlineColor(sf::Color(200, 200, 200));
	m_text.setCharacterSize(300);
}

void CGameOverView::InitSubText(const std::string & textMessage, const std::string & fontPath)
{
	InitSubTextFont(fontPath);
	m_subText.setFont(m_subTextFont);
	m_subText.setString(textMessage);
	m_subText.setFillColor(sf::Color(255, 255, 255));
	m_subText.setOutlineThickness(3);
	m_subText.setOutlineColor(sf::Color(0, 0, 0));
	m_subText.setCharacterSize(100);
}
