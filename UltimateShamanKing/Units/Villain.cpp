// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Villain.h"

void CVillain::Process(const std::vector<TmxObject> &collisionBlocks)
{
	UpdateCollision(collisionBlocks);
	if (!collision.bottom)
	{
		jumping = true;
		downSpeed += gravity;
		Gravity();
	}
	Animate(m_animationClock);
}

void CVillain::UpdateDirection(float playerLeft)
{
	if (GetLeft() < playerLeft)
	{
		TurnRight();
	}
	else
	{
		TurnLeft();
	}
}

void CVillain::Animate(sf::Clock & animationClock)
{
	float deltaSec = animationClock.getElapsedTime().asSeconds();
	if (deltaSec > 0.2)
	{
		UpdateStayingSprite();
		animationClock.restart();
	}
}

void CVillain::UpdateStayingSprite()
{
	m_currentStayingSprite = (m_currentStayingSprite == 3) ? 0 : m_currentStayingSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startSpriteWidth;
	textureRect.top = m_startSpriteOffsetTop;
	m_modelSprite.setOrigin(0, 0);
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}

	switch (m_currentStayingSprite)
	{
		case 0:
			textureRect.left = offsetLeft + 0;
			break;
		case 1:
			textureRect.left = offsetLeft + 28;
			break;
		case 2:
			textureRect.left = offsetLeft + 59;
			break;
		case 3:
			textureRect.left = offsetLeft + 87;
			break;
		default:
			break;
	}
	m_modelSprite.setTextureRect(textureRect);
}
