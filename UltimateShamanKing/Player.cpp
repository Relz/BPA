// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Player.h"

void CPlayer::Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity)
{
	SetPosition(startPosition);
	this->movementSpeed = movementSpeed;
	this->upSpeed = upSpeed;
	this->startDownSpeed = downSpeed;
	this->gravity = gravity;
}

void CPlayer::Draw(sf::RenderTarget & target) const
{
	target.draw(m_sprite);
}

void CPlayer::SetSprite(const std::string & spriteName, const sf::IntRect & playerSpriteRect, float zoom)
{
	if (!m_texture.loadFromFile(spriteName))
	{
		throw std::invalid_argument("\"" + spriteName + "\" not found");
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(playerSpriteRect.left, playerSpriteRect.top, playerSpriteRect.width, playerSpriteRect.height));
	m_startOffsetLeft = playerSpriteRect.left;
	m_startOffsetTop = playerSpriteRect.top;
	m_startWidth = playerSpriteRect.width;
	m_startHeight = playerSpriteRect.height;
	m_sprite.setScale(zoom, zoom);
}

void CPlayer::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void CPlayer::SetPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

void CPlayer::MoveX()
{
	m_sprite.move(GetMovement().x, 0);
}

void CPlayer::Move(const sf::Vector2f & offset)
{
	m_sprite.move(offset);
}

void CPlayer::MoveProcess(const std::vector<TmxObject> & collisionBlocks, sf::Clock & clock)
{
	UpdateDirection();
	Animate(clock);
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

void CPlayer::Gravity()
{
	m_sprite.move(0, downSpeed);
}

float CPlayer::GetWidth() const
{
	return m_sprite.getGlobalBounds().width;
}

float CPlayer::GetHeight() const
{
	return m_sprite.getGlobalBounds().height;
}

float CPlayer::GetTop() const
{
	return m_sprite.getPosition().y;
}

float CPlayer::GetLeft() const
{
	return m_sprite.getPosition().x;
}

sf::IntRect CPlayer::GetRect() const
{
	return sf::IntRect(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetWidth()), static_cast<int>(GetHeight()));
}

sf::Vector2f CPlayer::GetPosition() const
{
	return sf::Vector2f(GetLeft(), GetTop());
}

void CPlayer::UpdateStayingSprite()
{
	m_currentStayingSprite = (m_currentStayingSprite == 3) ? 0 : m_currentStayingSprite + 1;
	sf::IntRect textureRect = m_sprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.top = m_startOffsetTop;
	textureRect.width = abs(textureRect.width);
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
	m_currentMovingSprite = (m_currentMovingSprite == 5) ? 0 : m_currentMovingSprite + 1;
	sf::IntRect textureRect = m_sprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.height = m_startHeight;
	textureRect.top = 91;
	textureRect.width = abs(textureRect.width);
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

void CPlayer::UpdateJumpingSprite()
{
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction.x = +1;
	}
	if (direction.x == 1 || direction.x == -1)
	{
		m_lastDirection.x = direction.x;
	}
}

void CPlayer::Animate(sf::Clock & clock)
{
	float deltaSec = clock.getElapsedTime().asSeconds();
	if (deltaSec > 0.1)
	{
		if (!jumping)
		{
			if (!IsStaying())
			{
				UpdateMovingSprite();
				clock.restart();
			}
		}
		else
		{
			UpdateJumpingSprite();
		}
	}
	if (deltaSec > 0.3)
	{
		if (!jumping && IsStaying())
		{
			UpdateStayingSprite();
		}
		clock.restart();
	}
}

static bool DoesObjectsPlacesInOneVertical(float object1LeftX, float object1RightX, float object2LeftX, float object2RightX)
{
	return object1RightX >= object2LeftX && object1LeftX <= object2RightX;
}

static bool DoesObjectsPlacesInOneHorizontal(float object1TopY, float object1BottomY, float object2TopY, float object2BottomY)
{
	return object1BottomY > object2TopY && object1TopY < object2BottomY;
}

void CPlayer::UpdateCollision(const std::vector<TmxObject> & tiles)
{
	collision = Collision();
	sf::IntRect playerRect = GetRect();
	sf::Vector2f playerMovement = GetMovement();

	const float futurePlayerTopY = playerRect.top + playerMovement.y;
	const float futurePlayerBottomY = futurePlayerTopY + playerRect.height;
	const float futurePlayerLeftX = playerRect.left + playerMovement.x;
	const float futurePlayerRightX = futurePlayerLeftX + playerRect.width;

	const float playerTopY = playerRect.top;
	const float playerBottomY = playerTopY + playerRect.height;
	const float playerLeftX = playerRect.left;
	const float playerRightX = playerLeftX + playerRect.width;

	bool XCollisionProcessed = false;
	bool YCollisionProcessed = false;
	for (const TmxObject & tile : tiles)
	{
		const float tileLeftX = tile.rect.left;
		const float tileRightX = tileLeftX + tile.rect.width;
		const float tileTopY = tile.rect.top;
		const float tileBottomY = tileTopY + tile.rect.height;

		if (!XCollisionProcessed)
		{
			bool playerPlacesInOneHorizontalWithTile = DoesObjectsPlacesInOneHorizontal(playerTopY, playerBottomY, tileTopY, tileBottomY);
			bool isLeftCollision = futurePlayerLeftX <= tileRightX && futurePlayerRightX >= tileRightX && playerLeftX >= tileRightX;
			bool isRightCollision = futurePlayerRightX >= tileLeftX && futurePlayerLeftX <= tileLeftX && playerRightX <= tileLeftX;

			if (playerPlacesInOneHorizontalWithTile && (isLeftCollision || isRightCollision))
			{
				collision.left = isLeftCollision;
				collision.right = isRightCollision;
				XCollisionProcessed = true;
			}
		}

		if (!YCollisionProcessed)
		{
			bool playerPlacesInOneVerticalWithTile = DoesObjectsPlacesInOneVertical(playerLeftX, playerRightX, tileLeftX, tileRightX);
			bool isTopCollision = futurePlayerTopY <= tileBottomY && futurePlayerBottomY >= tileBottomY/* && playerTopY >= tileBottomY*/;
			bool isBottomCollision = futurePlayerBottomY >= tileTopY && futurePlayerTopY <= tileTopY/* && playerBottomY < tileTopY*/;

			if (playerPlacesInOneVerticalWithTile && (isTopCollision || isBottomCollision))
			{
				collision.top = isTopCollision;
				collision.bottom = isBottomCollision;
				YCollisionProcessed = true;
				if (collision.top)
				{
					SetPosition(GetPosition().x, tileBottomY + 1);
				}
				if (collision.bottom && downSpeed > 0)
				{
					SetPosition(GetPosition().x, tileTopY - GetHeight());
				}
			}
		}

		if (XCollisionProcessed && YCollisionProcessed)
		{
			break;
		}
	}
}

static sf::Vector2f Round(const sf::Vector2f &value)
{
	return sf::Vector2f(roundf(value.x), roundf(value.y));
}

sf::Vector2f CPlayer::GetMovement() const
{
	return Round({direction.x * movementSpeed, direction.y * downSpeed});
}

bool CPlayer::IsStaying() const
{
	return (direction.x == 0 && direction.y == 0);
}
