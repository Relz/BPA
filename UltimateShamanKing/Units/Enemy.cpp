// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Enemy.h"

void CEnemy::Init(const std::wstring & name,
                  sf::Vector2f startPosition,
                  float movementSpeed,
                  float upSpeed,
                  float downSpeed,
                  float gravity,
                  float dyingTimeSec,
                  float movingCooldownSec,
                  size_t HP,
                  size_t strength)
{
	CUnit::Init(name, startPosition, movementSpeed, upSpeed, downSpeed, gravity, dyingTimeSec, HP, strength);
	m_movingCooldownSec = movingCooldownSec;
}

void CEnemy::Process(const std::vector<TmxObject> & collisionBlocks)
{
	Animate(m_animationClock);
	UpdateCollision(collisionBlocks);
	if ((GetDirection().x > 0 && !collision.right) || (GetDirection().x < 0 && !collision.left))
	{
		MoveX();
	}
	if (IsAlive())
	{
		UpdateDirection();
		if (IsStaying() && m_stayingClock.getElapsedTime().asSeconds() > m_stayingTime)
		{
			if (myRandom.GetRandomValue(0, 1) == 0)
			{
				TurnLeft();
			}
			else
			{
				TurnRight();
			}
			m_movingClock.restart();
		}
		bool isAbyssOnSide = IsAbyssOnSide(collisionBlocks);
		if (collision.left || collision.right ||
		    (isAbyssOnSide && collision.bottom && GetDirection().x == 1) ||
		    (isAbyssOnSide && collision.bottom && GetDirection().x == -1))
		{
			TurnAround();
		}
	}
	else
	{
		if ((collision.right || collision.left) && !IsAlive())
		{
			Stop();
		}
		if ((collision.top || collision.bottom) && movementSpeed > 0)
		{
			movementSpeed -= 0.2;
		}
	}
	if (collision.top)
	{
		downSpeed = 0;
	}
	if (collision.bottom)
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

void CEnemy::Die()
{
	CUnit::Die();
	m_justDied = true;
}

void CEnemy::CreateNewSnowball(float directionX)
{
	m_snowball = std::unique_ptr<CSnowball>(new CSnowball);
	sf::Vector2f playerPosition = GetPosition();
	playerPosition.y += GetHeight() / 3;
	m_snowball->Init(playerPosition, directionX, myRandom.GetRandomValue(5, 7), myRandom.GetRandomValue(4, 6), 10);
	m_snowball->SetImage("../res/Images/snowball.png", 0.2);
}

CSnowball * CEnemy::GetSnowball() const
{
	return m_snowball.get();
}

void CEnemy::DestroySnowball()
{
	m_snowball = nullptr;
}

void CEnemy::UpdateDirection()
{
	if (m_movingClock.getElapsedTime().asSeconds() >= m_movingCooldownSec && !IsStaying())
	{
		Stop();
		m_stayingClock.restart();
	}
}

void CEnemy::Animate(sf::Clock & animationClock)
{
	float deltaSec = animationClock.getElapsedTime().asSeconds();
	if (IsAlive())
	{
		if (deltaSec > 0.1)
		{
			if (jumping)
			{
				UpdateJumpingSprite();
			}
			else if (!IsStaying())
			{
				UpdateMovingSprite();
				animationClock.restart();
			}
			if (deltaSec > 0.3)
			{
				if (!jumping && IsStaying())
				{
					UpdateStayingSprite();
				}
				animationClock.restart();
			}
		}
	}
	else if (deltaSec > 1.0 || m_justDied)
	{
		m_justDied = false;
		UpdateDyingSprite();
		animationClock.restart();
	}
}


void CEnemy::UpdateStayingSprite()
{
	m_currentMovingSprite = 0;
	m_currentStayingSprite = (m_currentStayingSprite == 2) ? 0 : m_currentStayingSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.top = m_startSpriteOffsetTop;
	textureRect.width = abs(textureRect.width);
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}

	switch (m_currentStayingSprite)
	{
		case 0:
			textureRect.height = m_startSpriteHeight;
			textureRect.left = offsetLeft + 0;
			break;
		case 1:
			textureRect.height = m_startSpriteHeight;
			textureRect.left = offsetLeft + 27;
			break;
		case 2:
			textureRect.height = m_startSpriteHeight;
			textureRect.left = offsetLeft + 54;
			break;
		default:
			break;
	}
	m_modelSprite.setTextureRect(textureRect);
}

void CEnemy::UpdateMovingSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = (m_currentMovingSprite == 5) ? 0 : m_currentMovingSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.height = m_startSpriteHeight;
	textureRect.top = 52;
	textureRect.width = abs(textureRect.width);
	if (GetLastDirection().x == 1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}
	switch (m_currentMovingSprite)
	{
		case 0:
			textureRect.left = offsetLeft + 1;
			break;
		case 1:
			textureRect.left = offsetLeft + 33;
			break;
		case 2:
			textureRect.left = offsetLeft + 63;
			break;
		case 3:
			textureRect.left = offsetLeft + 94;
			break;
		case 4:
			textureRect.left = offsetLeft + 126;
			break;
		case 5:
			textureRect.left = offsetLeft + 165;
			break;
		default:
			break;
	}
	m_modelSprite.setTextureRect(textureRect);
}

void CEnemy::UpdateJumpingSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = 0;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.height = m_startSpriteHeight;
	textureRect.top = 218;
	textureRect.width = abs(textureRect.width);
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}

	textureRect.left = (downSpeed > 0) ? offsetLeft + 20 : offsetLeft + 40;
	m_modelSprite.setTextureRect(textureRect);
}

void CEnemy::UpdateDyingSprite()
{
	m_currentDyingSprite = (m_currentDyingSprite == 1) ? 0 : m_currentDyingSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startSpriteHeight;
	textureRect.height = abs(textureRect.width) / 2;
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}
	switch (m_currentDyingSprite)
	{
		case 0:
			textureRect.top = 50;
			textureRect.left = offsetLeft + 213;
			break;
		case 1:
			textureRect.top = 75;
			textureRect.left = offsetLeft + 211;
			break;
		default:
			break;
	}
	m_modelSprite.setTextureRect(textureRect);
}
