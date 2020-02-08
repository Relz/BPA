// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Beloved.h"

void CBeloved::Process(const std::vector<TmxObject> &collisionBlocks)
{
	UpdateCollision(collisionBlocks);
	if (!collision.bottom)
	{
		jumping = true;
		downSpeed += gravity;
		Gravity();
	}
}

void CBeloved::UpdateDirection(float playerLeft)
{
	if (GetLeft() < playerLeft)
	{
		TurnRight();
	}
	else
	{
		TurnLeft();
	}

	sf::IntRect rect = m_modelSprite.getTextureRect();
	if (GetDirection().x == 1)
	{
		rect.left = 0;
		rect.width = m_startSpriteWidth;
	}
	else
	{
		rect.left = m_startSpriteWidth;
		rect.width = -m_startSpriteWidth;
	}
	m_modelSprite.setTextureRect(rect);
}
