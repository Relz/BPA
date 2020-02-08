// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "MoneyPanel.h"

void CMoneyPanel::Init(const std::string & currencyName, float padding)
{
	m_currencyName = currencyName;
	if (!m_font.loadFromFile("../res/Fonts/CyrilicOld.ttf"))
	{
		throw std::invalid_argument("Failed to load \"../res/Fonts/CyrilicOld.ttf\"");
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color::White);
	m_background.setFillColor(sf::Color(0, 150, 100, 100));
	m_padding = padding;
}

void CMoneyPanel::Draw(sf::RenderTarget & target) const
{
	target.draw(m_background);
	target.draw(m_text);
}

void CMoneyPanel::SetPosition(const sf::Vector2f & position)
{
	m_background.setPosition(position);
	m_text.setPosition(position.x + m_padding, position.y + m_padding);
	m_background.setSize({m_text.getGlobalBounds().width + m_padding * 2, m_text.getGlobalBounds().height + m_padding * 2});
}

static std::string DiscardFractionalPart(const std::string & floatStr, size_t depth)
{
	std::string result;
	for (size_t i = 0; i < floatStr.length(); ++i)
	{
		result +=floatStr[i];
		if (floatStr[i] == '.' && i + depth < floatStr.size())
		{
			for (size_t j = 1; j <= depth; ++j)
			{
				result += floatStr[i + j];
			}
			break;
		}
	}
	return result;
}

void CMoneyPanel::SetMoney(float value)
{
	m_money = value;
	std::string valueStr = DiscardFractionalPart(std::to_string(m_money), 2);
	m_text.setString(m_currencyName + ": " + valueStr);
}
