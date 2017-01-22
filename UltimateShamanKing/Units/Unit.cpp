// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Unit.h"

bool CUnit::DoesObjectsPlacesInOneVertical(float object1LeftX, float object1RightX, float object2LeftX, float object2RightX)
{
	return object1RightX >= object2LeftX && object1LeftX <= object2RightX;
}

bool CUnit::DoesObjectsPlacesInOneHorizontal(float object1TopY, float object1BottomY, float object2TopY, float object2BottomY)
{
	return object1BottomY > object2TopY && object1TopY < object2BottomY;
}

void CUnit::GetCollision(const sf::IntRect & objectRect,
                         const sf::IntRect & unitRect,
                         const sf::IntRect & unitFutureRect,
                         float unitDirectionX,
                         float playerWidth,
                         float & out_collisionBlockTop,
                         float & out_collisionBlockBottom,
                         Collision & out_collision)
{

	float unitTop = unitRect.top;
	float unitBottom = unitTop + unitRect.height;
	float unitLeft = unitRect.left;
	float unitRight = unitLeft + unitRect.width;

	float unitFutureTop = unitFutureRect.top;
	float unitFutureBottom = unitFutureTop + unitFutureRect.height;
	float unitFutureLeft = unitFutureRect.left;
	float unitFutureRight = unitFutureLeft + unitFutureRect.width;

	if(unitDirectionX == -1)
	{
		unitRight = unitRect.left + playerWidth;
		unitLeft = unitRight - unitRect.width;
		unitFutureRight = unitFutureRect.left + playerWidth;
		unitFutureLeft = unitFutureRight - unitFutureRect.width;
	}

	float objectLeft = objectRect.left;
	float objectRight = objectLeft + objectRect.width;
	float objectTop = objectRect.top;
	float objectBottom = objectTop + objectRect.height;

	if (DoesObjectsPlacesInOneHorizontal(unitTop, unitBottom, objectTop, objectBottom))
	{
		bool isLeftCollision = unitFutureLeft <= objectRight && unitFutureRight >= objectRight;
		if (unitLeft != unitFutureLeft)
		{
			isLeftCollision = isLeftCollision && unitLeft >= objectRight;
		}
		bool isRightCollision = unitFutureRight >= objectLeft && unitFutureLeft <= objectLeft;
		if (unitRight != unitFutureRight)
		{
			isRightCollision = isRightCollision && unitRight <= objectLeft;
		}
		if (isLeftCollision)
		{
			out_collision.left = true;
		}
		if (isRightCollision)
		{
			out_collision.right = true;
		}
	}

	if (DoesObjectsPlacesInOneVertical(unitLeft, unitRight, objectLeft, objectRight))
	{
		bool isTopCollision = unitFutureTop <= objectBottom && unitFutureBottom >= objectBottom;
		bool isBottomCollision = unitFutureBottom >= objectTop && unitFutureTop <= objectTop;
		if (isTopCollision)
		{
			out_collision.top = true;
			out_collisionBlockBottom = objectBottom;
		}
		if (isBottomCollision)
		{
			out_collision.bottom = true;
			out_collisionBlockTop = objectTop;
		}
	}
}

void CUnit::Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity, float dyingTime)
{
	SetPosition(startPosition);
	this->movementSpeed = movementSpeed;
	this->upSpeed = upSpeed;
	this->startDownSpeed = downSpeed;
	this->gravity = gravity;
	this->m_dyingTimeSec = dyingTime;
}

void CUnit::Draw(sf::RenderTarget & target) const
{
	target.draw(m_sprite);
}

void CUnit::SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom)
{
	if (!m_texture.loadFromFile(spritePath))
	{
		throw std::invalid_argument("\"" + spritePath + "\" not found");
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(playerSpriteRect.left, playerSpriteRect.top, playerSpriteRect.width, playerSpriteRect.height));
	m_startSpriteOffsetLeft = playerSpriteRect.left;
	m_startSpriteOffsetTop = playerSpriteRect.top;
	m_startSpriteWidth = playerSpriteRect.width;
	m_startSpriteHeight = playerSpriteRect.height;
	m_sprite.setScale(zoom, zoom);
	m_width = m_sprite.getGlobalBounds().width;
	m_height = m_sprite.getGlobalBounds().height;
}

void CUnit::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void CUnit::SetPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
}

void CUnit::SetImpuls(float x, float y)
{
	jumping = true;
	downSpeed -= y;
	if (x > 0)
	{
		direction.x = 1;
	}
	else if (x < 0)
	{
		direction.x = -1;
	}
}

void CUnit::MoveX()
{
	m_sprite.move(GetMovement().x, 0);
}

void CUnit::Move(const sf::Vector2f & offset)
{
	m_sprite.move(offset);
}

void CUnit::Gravity()
{
	m_sprite.move(0, downSpeed);
}

float CUnit::GetWidth() const
{
	return m_width;
}

float CUnit::GetSpriteWidth() const
{
	return m_sprite.getGlobalBounds().width;
}

float CUnit::GetHeight() const
{
	return m_sprite.getGlobalBounds().height;
}

float CUnit::GetSpriteHeight() const
{
	return m_height;
}

float CUnit::GetTop() const
{
	return m_sprite.getPosition().y;
}

float CUnit::GetLeft() const
{
	return m_sprite.getPosition().x;
}

sf::IntRect CUnit::GetRect() const
{
	return sf::IntRect(static_cast<int>(GetLeft()),
	                   static_cast<int>(GetTop()),
	                   static_cast<int>(GetWidth()),
	                   static_cast<int>(GetHeight()));
}

sf::IntRect CUnit::GetFutureRect() const
{
	sf::Vector2f unitMovement = GetMovement();
	return sf::IntRect(static_cast<int>(GetLeft() + unitMovement.x),
	                   static_cast<int>(GetTop() + unitMovement.y),
	                   static_cast<int>(GetWidth()),
	                   static_cast<int>(GetHeight()));
}

sf::IntRect CUnit::GetSpriteRect() const
{
	return sf::IntRect(static_cast<int>(GetLeft()),
	                   static_cast<int>(GetTop()),
	                   static_cast<int>(GetSpriteWidth()),
	                   static_cast<int>(GetSpriteHeight()));
}

sf::IntRect CUnit::GetFutureSpriteRect() const
{
	sf::Vector2f unitMovement = GetMovement();
	return sf::IntRect(static_cast<int>(GetLeft() + unitMovement.x),
	                   static_cast<int>(GetTop() + unitMovement.y),
	                   static_cast<int>(GetSpriteWidth()),
	                   static_cast<int>(GetSpriteHeight()));
}

sf::Vector2f CUnit::GetPosition() const
{
	return sf::Vector2f(GetLeft(), GetTop());
}

sf::Vector2f CUnit::GetMovement() const
{
	return sf::Vector2f(roundf(direction.x * movementSpeed), roundf(direction.y * downSpeed));
}

sf::Vector2f CUnit::GetDirection() const
{
	return m_lastDirection;
}

float CUnit::GetDyingTimeSec() const
{
	return m_dyingTimeSec;
}

float CUnit::GetDyingClockSec() const
{
	return m_dyingClock.getElapsedTime().asSeconds();
}

float CUnit::GetUpSpeed() const
{
	return upSpeed;
}

bool CUnit::IsStaying() const
{
	return (direction.x == 0 && direction.y == 0);
}

bool CUnit::IsAlive() const
{
	return !m_dead;
}

bool CUnit::DoesAttacking() const
{
	return m_attacking;
}

bool CUnit::DoesJumping() const
{
	return jumping;
}


void CUnit::UpdateCollision(const std::vector<TmxObject> & collisionBlocks)
{
	float collisionBlockTop = 0;
	float collisionBlockBottom = 0;
	collision = GetCollision(collisionBlocks, GetLeft(), GetTop(), collisionBlockTop, collisionBlockBottom);
	if (collision.bottom && downSpeed > 0 && IsAlive())
	{
		SetPosition(GetPosition().x, collisionBlockTop - m_height + downSpeed);
	}
}

bool CUnit::IsAbyssOnSide(const std::vector<TmxObject> & collisionBlocks) const
{
	float collisionBlockTop = 0;
	float collisionBlockBottom = 0;
	bool isLeftAbyss = !GetCollision(collisionBlocks, GetLeft() - m_width, GetTop(), collisionBlockTop, collisionBlockBottom).bottom;
	bool isRightAbyss = !GetCollision(collisionBlocks, GetLeft() + m_width, GetTop(), collisionBlockTop, collisionBlockBottom).bottom;
	return isLeftAbyss || isRightAbyss;
}

Collision CUnit::GetCollision(const std::vector<TmxObject> & collisionBlocks,
							  float unitLeft,
							  float unitTop,
							  float & out_collisionBlockTop,
							  float & out_collisionBlockBottom) const
{
	Collision result;

	sf::IntRect unitRect = {unitLeft, unitTop, GetWidth(), GetHeight()};

	sf::Vector2f unitMovement = GetMovement();
	float unitFutureLeft = unitLeft + unitMovement.x;
	float unitFutureTop = unitTop + unitMovement.y;

	sf::IntRect unitFutureRect = {unitFutureLeft, unitFutureTop, GetWidth(), GetHeight()};

	for (const TmxObject & collisionBlock : collisionBlocks)
	{
		GetCollision(collisionBlock.rect,
		             unitRect,
		             unitFutureRect,
		             GetDirection().x,
		             GetWidth(),
		             out_collisionBlockTop, out_collisionBlockBottom, result);
		if ((result.left || result.right) && (result.top || result.bottom))
		{
			break;
		}
	}
	return result;
}

void CUnit::Die()
{
	m_dyingClock.restart();
	m_dead = true;
}