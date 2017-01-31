// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Replica.h"

static std::wstring GetMultilineString(const sf::Text & text, float stringWidth)
{
	std::wstring result;
	std::wstring textMessage = text.getString();
	int lineCount = static_cast<int>(ceil(text.getGlobalBounds().width / stringWidth));
	int charactersPerNewLine = static_cast<int>(textMessage.length() / lineCount);
	for (size_t i = 0; i < textMessage.length(); ++i)
	{
		result += textMessage[i];
		if (i % charactersPerNewLine == 0 && i != 0)
		{
			result += '\n';
		}
	}
	return result;
}

CReplica::CReplica(const std::wstring & name, sf::Sprite * avatarSprite, const std::wstring & message,
                   const sf::Vector2f & position, float width)
		: m_avatarSprite(avatarSprite)
{
	if (!m_nameFont.loadFromFile("../res/Fonts/arial.ttf"))
	{
		throw std::invalid_argument("Failed to load \"../res/Fonts/arial.ttf\"");
	}
	if (!m_messageFont.loadFromFile("../res/Fonts/CyrilicOld.ttf"))
	{
		throw std::invalid_argument("Failed to load \"../res/Fonts/CyrilicOld.ttf\"");
	}
	avatarSprite->setPosition(position);
	float avatarWidth = avatarSprite->getGlobalBounds().width;
	float avatarHeight = avatarSprite->getGlobalBounds().height;
	float messageBackgroundThickness = 5;
	float messageBackgroundWidth = width - avatarWidth - (messageBackgroundThickness + 1);
	float messageBackgroundHeight = avatarHeight - (messageBackgroundThickness + 1);
	m_messageBackground.setPosition(position.x + avatarWidth, position.y);
	m_messageBackground.setSize(sf::Vector2f(messageBackgroundWidth, messageBackgroundHeight));
	m_messageBackground.setFillColor(sf::Color(0, 0, 0, 128));
	m_messageBackground.setOutlineThickness(messageBackgroundThickness);
	m_messageBackground.setOutlineColor(sf::Color(0, 0, 0, 200));
	m_name.setFont(m_nameFont);
	m_name.setCharacterSize(70);
	m_name.setString(name);
	m_name.setFillColor(sf::Color(50, 220, 50));
	m_name.setOutlineThickness(2);
	m_name.setOutlineColor(sf::Color(50, 50, 50));
	m_name.setPosition(m_messageBackground.getPosition());
	m_message.setFont(m_messageFont);
	m_message.setCharacterSize(60);
	m_message.setString(message);
	m_message.setString(GetMultilineString(m_message, messageBackgroundWidth));
	m_message.setFillColor(sf::Color(220, 220, 220));
	m_message.setOutlineThickness(2);
	m_message.setOutlineColor(sf::Color(50, 50, 50));
	m_message.setPosition(m_messageBackground.getPosition().x, m_messageBackground.getPosition().y + 70);
}

void CReplica::Draw(sf::RenderTarget & target) const
{
	target.draw(*m_avatarSprite);
	target.draw(m_messageBackground);
	target.draw(m_name);
	target.draw(m_message);
}
