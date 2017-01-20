// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Player.h"

void CPlayer::MoveProcess(const std::vector<TmxObject> & collisionBlocks)
{
	float deltaSec = m_animationClock.getElapsedTime().asSeconds();
	UpdateDirection();
	if (DoesAttack() && m_attackingClock.getElapsedTime().asSeconds() > 0.5)
	{
		attacking = true;
		m_attackingClock.restart();
	}
	if (m_attackingClock.getElapsedTime().asSeconds() > 0.5)
	{
		attacking = false;
	}
	Animate(m_animationClock);
	UpdateCollision(collisionBlocks);
	if ((direction.x > 0 && !collision.right) || (direction.x < 0 && !collision.left))
	{
		MoveX();
	}
	bool canJump = !jumping && direction.y == -1 && !collision.top;
	if (canJump)
	{
		jumping = true;
		downSpeed -= upSpeed * 3.5;
	}
	if (collision.top && downSpeed < 0)
	{
		downSpeed = 0;
	}
	if (collision.bottom && !canJump)
	{
		downSpeed = startDownSpeed;
		jumping = false;
	}
	else
	{
		jumping = true;
		downSpeed += gravity;
		Gravity();
	}
}

bool CPlayer::DoesAttack() const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
}

void CPlayer::UpdateStayingSprite()
{
	m_currentMovingSprite = 0;
	m_currentStayingSprite = (m_currentStayingSprite == 3) ? 0 : m_currentStayingSprite + 1;
	sf::IntRect textureRect = m_sprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startWidth;
	textureRect.top = m_startOffsetTop;
	textureRect.width = abs(textureRect.width);
	m_sprite.setOrigin(0, 0);
	if (m_lastDirection.x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}

	switch (m_currentStayingSprite)
	{
		case 0:
			textureRect.height = m_startHeight;
			textureRect.left = offsetLeft + 6;
			break;
		case 1:
			textureRect.height = m_startHeight + 1;
			textureRect.left = offsetLeft + 39;
			break;
		case 2:
			textureRect.height = m_startHeight + 2;
			textureRect.left = offsetLeft + 72;
			break;
		case 3:
			textureRect.height = m_startHeight + 1;
			textureRect.left = offsetLeft + 39;
			break;
		default:
			break;
	}
	m_sprite.setTextureRect(textureRect);
}

void CPlayer::UpdateMovingSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = (m_currentMovingSprite == 5) ? 0 : m_currentMovingSprite + 1;
	sf::IntRect textureRect = m_sprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startWidth;
	textureRect.height = m_startHeight;
	textureRect.top = 91;
	textureRect.width = abs(textureRect.width);
	m_sprite.setOrigin(0, 0);
	if (m_lastDirection.x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}
	switch (m_currentMovingSprite)
	{
		case 0:
			textureRect.left = offsetLeft + 0;
			break;
		case 1:
			textureRect.left = offsetLeft + 30;
			break;
		case 2:
			textureRect.left = offsetLeft + 66;
			break;
		case 3:
			textureRect.left = offsetLeft + 100;
			break;
		case 4:
			textureRect.top = 95;
			textureRect.left = offsetLeft + 135;
			break;
		case 5:
			textureRect.top = 95;
			textureRect.left = offsetLeft + 168;
			break;
		default:
			break;
	}
	m_sprite.setTextureRect(textureRect);
}

void CPlayer::UpdateAttackingSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = (m_currentMovingSprite == 4) ? 0 : m_currentMovingSprite + 1;
	sf::IntRect textureRect = m_sprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startWidth;
	textureRect.height = m_startHeight;
	textureRect.top = 91;
	textureRect.width = abs(textureRect.width);
	m_sprite.setOrigin(0, 0);
	switch (m_currentMovingSprite)
	{
		case 0:
			if (m_lastDirection.x == -1)
			{
				offsetLeft = textureRect.width;
				textureRect.width = -textureRect.width;
				m_sprite.setOrigin(-textureRect.width - m_startWidth, 0);
			}
			textureRect.left = offsetLeft + 412;
			break;
		case 1:
			textureRect.width = 60;
			if (m_lastDirection.x == -1)
			{
				offsetLeft = textureRect.width;
				textureRect.width = -textureRect.width;
				m_sprite.setOrigin(-textureRect.width - m_startWidth, 0);
			}
			textureRect.left = offsetLeft + 445;
			break;
		case 2:
			textureRect.width = 70;
			if (m_lastDirection.x == -1)
			{
				offsetLeft = textureRect.width;
				textureRect.width = -textureRect.width;
				m_sprite.setOrigin(-textureRect.width - m_startWidth, 0);
			}
			textureRect.left = offsetLeft + 511;
			break;
		case 3:
			textureRect.width = 70;
			if (m_lastDirection.x == -1)
			{
				offsetLeft = textureRect.width;
				textureRect.width = -textureRect.width;
				m_sprite.setOrigin(-textureRect.width - m_startWidth, 0);
			}
			textureRect.left = offsetLeft + 590;
			break;
		case 4:
			textureRect.width = 70;
			if (m_lastDirection.x == -1)
			{
				offsetLeft = textureRect.width;
				textureRect.width = -textureRect.width;
				m_sprite.setOrigin(-textureRect.width - m_startWidth, 0);
			}
			textureRect.top = 130;
			textureRect.left = offsetLeft + 629;
			break;
		default:
			break;
	}
	m_sprite.setTextureRect(textureRect);
}

void CPlayer::UpdateJumpingSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = 0;
	sf::IntRect textureRect = m_sprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.height = m_startHeight;
	textureRect.top = 149;
	textureRect.width = abs(textureRect.width);
	if (m_lastDirection.x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}

	textureRect.left = (downSpeed > 0) ? offsetLeft + 156 : offsetLeft + 100;
	m_sprite.setTextureRect(textureRect);
}

void CPlayer::UpdateDirection()
{
	direction = sf::Vector2f();

	static bool canJump = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (canJump)
		{
			canJump = false;
			direction.y = -1;
		}
	}
	else
	{
		canJump = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !attacking)
	{
		direction.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !attacking)
	{
		direction.x = +1;
	}
	if (direction.x == 1 || direction.x == -1)
	{
		m_lastDirection.x = direction.x;
	}
}

void CPlayer::Animate(sf::Clock & animationClock)
{
	float deltaSec = animationClock.getElapsedTime().asSeconds();
	if (deltaSec > 0.1)
	{
		if (!attacking)
		{
			if (!jumping)
			{
				if (!IsStaying())
				{
					UpdateMovingSprite();
					animationClock.restart();
				}
				else if (deltaSec > 0.3)
				{
					UpdateStayingSprite();
					animationClock.restart();
				}
			}
			else
			{
				UpdateJumpingSprite();
			}
		}
		else
		{
			UpdateAttackingSprite();
			animationClock.restart();
		}
	}
}

void CPlayer::Die()
{
	CUnit::Die();
}