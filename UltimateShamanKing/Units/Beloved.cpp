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
	direction.x = (GetLeft() < playerLeft) ? 1 : -1;
	if (direction.x == 1 || direction.x == -1)
	{
		m_lastDirection.x = direction.x;
	}

	sf::IntRect rect = m_sprite.getTextureRect();
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
	m_sprite.setTextureRect(rect);
}
