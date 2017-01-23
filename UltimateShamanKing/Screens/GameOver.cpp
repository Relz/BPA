#include "../stdafx.h"
#include "GameOver.h"

CGameOver::CGameOver()
{
	InitBackground("../res/Images/Game Over.png");
	InitText("Game Over", "../res/Fonts/Wizards Magic.ttf");
	InitSubText("Press Enter to continue", "../res/Fonts/arial.ttf");
}

void CGameOver::Draw(sf::RenderTarget & target)
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

void CGameOver::SetWindowCenter(const sf::Vector2f & windowCenter)
{
	m_windowCenter = windowCenter;
}

void CGameOver::SetWindowSize(const sf::Vector2u & windowSize)
{
	m_windowSize = windowSize;
}

void CGameOver::SetBackgroundScale(float x, float y)
{
	m_background.setScale(x, y);
}

float CGameOver::GetBackgroundWidth() const
{
	return m_background.getLocalBounds().width;
}

void CGameOver::InitBackground(const std::string & imagePath)
{
	if (!m_backgroundTexture.loadFromFile(imagePath))
	{
		throw std::invalid_argument("Failed to load \"" + imagePath + "\"");
	}
	m_background.setTexture(m_backgroundTexture);
}

void CGameOver::InitTextFont(const std::string &fontPath)
{
	if (!m_textFont.loadFromFile(fontPath))
	{
		throw std::invalid_argument("Failed to load \"" + fontPath + "\"");
	}
}

void CGameOver::InitSubTextFont(const std::string &fontPath)
{
	if (!m_subTextFont.loadFromFile(fontPath))
	{
		throw std::invalid_argument("Failed to load \"" + fontPath + "\"");
	}
}

void CGameOver::InitText(const std::string & textMessage, const std::string & fontPath)
{
	InitTextFont(fontPath);
	m_text.setFont(m_textFont);
	m_text.setString(textMessage);
	m_text.setFillColor(sf::Color(200, 0, 0));
	m_text.setOutlineThickness(5);
	m_text.setOutlineColor(sf::Color(200, 200, 200));
	m_text.setCharacterSize(300);
}

void CGameOver::InitSubText(const std::string & textMessage, const std::string & fontPath)
{
	InitSubTextFont(fontPath);
	m_subText.setFont(m_subTextFont);
	m_subText.setString(textMessage);
	m_subText.setFillColor(sf::Color(255, 255, 255));
	m_subText.setOutlineThickness(3);
	m_subText.setOutlineColor(sf::Color(0, 0, 0));
	m_subText.setCharacterSize(100);
}
