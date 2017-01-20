// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Unit.h"

void CUnit::Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity)
{
	SetPosition(startPosition);
	this->movementSpeed = movementSpeed;
	this->upSpeed = upSpeed;
	this->startDownSpeed = downSpeed;
	this->gravity = gravity;
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
	m_startHeight = m_height;
}

void CUnit::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void CUnit::SetPosition(const sf::Vector2f & position)
{
	m_sprite.setPosition(position);
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
	return m_sprite.getGlobalBounds().width;
}

float CUnit::GetHeight() const
{
	return m_sprite.getGlobalBounds().height;
}

float CUnit::GetTop() const
{
	return m_sprite.getPosition().y;
}

float CUnit::GetLeft() const
{
	return m_sprite.getPosition().x;
}

sf::Vector2f CUnit::GetPosition() const
{
	return sf::Vector2f(GetLeft(), GetTop());
}

static bool DoesObjectsPlacesInOneVertical(float object1LeftX, float object1RightX, float object2LeftX, float object2RightX)
{
	return object1RightX >= object2LeftX && object1LeftX <= object2RightX;
}

static bool DoesObjectsPlacesInOneHorizontal(float object1TopY, float object1BottomY, float object2TopY, float object2BottomY)
{
	return object1BottomY > object2TopY && object1TopY < object2BottomY;
}

void CUnit::UpdateCollision(const std::vector<TmxObject> & collisionBlocks)
{
	float collisionBlockTop = 0;
	float collisionBlockBottom = 0;
	collision = GetCollision(collisionBlocks, GetLeft(), GetTop(), collisionBlockTop, collisionBlockBottom);
	if (collision.bottom && downSpeed > 0)
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

	float unitRight = unitLeft + m_width;
	float unitBottom = unitTop + m_height;

	sf::Vector2f unitMovement = GetMovement();
	float futureUnitTop = unitTop + unitMovement.y;
	float futureUnitBottom = futureUnitTop + m_height;
	float futureUnitLeft = unitLeft + unitMovement.x;
	float futureUnitRight = futureUnitLeft + m_width;

	for (const TmxObject & collisionBlock : collisionBlocks)
	{
		GetCollision(collisionBlock,
					 unitTop, unitRight, unitBottom, unitLeft,
					 futureUnitTop, futureUnitRight, futureUnitBottom, futureUnitLeft,
					 out_collisionBlockTop, out_collisionBlockBottom, result);
		if ((result.left || result.right) && (result.top || result.bottom))
		{
			break;
		}
	}
	return result;
}

void CUnit::GetCollision(const TmxObject & collisionBlock,
							  float unitTop,
							  float unitRight,
							  float unitBottom,
							  float unitLeft,
							  float futureUnitTop,
							  float futureUnitRight,
							  float futureUnitBottom,
							  float futureUnitLeft,
							  float & out_collisionBlockTop,
							  float & out_collisionBlockBottom,
							  Collision & out_collision) const
{
	float collisionBlockLeft = collisionBlock.rect.left;
	float collisionBlockRight = collisionBlockLeft + collisionBlock.rect.width;
	float collisionBlockTop = collisionBlock.rect.top;
	float collisionBlockBottom = collisionBlockTop + collisionBlock.rect.height;

	bool playerPlacesInOneHorizontalWithTile = DoesObjectsPlacesInOneHorizontal(unitTop, unitBottom, collisionBlockTop, collisionBlockBottom);
	bool isLeftCollision = futureUnitLeft <= collisionBlockRight && futureUnitRight >= collisionBlockRight && unitLeft >= collisionBlockRight;
	bool isRightCollision = futureUnitRight >= collisionBlockLeft && futureUnitLeft <= collisionBlockLeft && unitRight <= collisionBlockLeft;

	if (playerPlacesInOneHorizontalWithTile)
	{
		if (isLeftCollision)
		{
			out_collision.left = isLeftCollision;
		}
		if (isRightCollision)
		{
			out_collision.right = isRightCollision;
		}
	}

	bool playerPlacesInOneVerticalWithTile = DoesObjectsPlacesInOneVertical(unitLeft, unitRight, collisionBlockLeft, collisionBlockRight);
	bool isTopCollision = futureUnitTop <= collisionBlockBottom && futureUnitBottom >= collisionBlockBottom;
	bool isBottomCollision = futureUnitBottom >= collisionBlockTop && futureUnitTop <= collisionBlockTop;

	if (playerPlacesInOneVerticalWithTile)
	{
		if (isTopCollision)
		{
			out_collision.top = isTopCollision;
			out_collisionBlockBottom = collisionBlockBottom;
		}
		if (isBottomCollision)
		{
			out_collision.bottom = isBottomCollision;
			out_collisionBlockTop = collisionBlockTop;
		}
	}
}

static sf::Vector2f Round(const sf::Vector2f &value)
{
	return sf::Vector2f(roundf(value.x), roundf(value.y));
}

sf::Vector2f CUnit::GetMovement() const
{
	return Round({direction.x * movementSpeed, direction.y * downSpeed});
}

bool CUnit::IsStaying() const
{
	return (direction.x == 0 && direction.y == 0);
}

bool CUnit::IsAlive() const
{
	return !m_dead;
}

void CUnit::Die()
{
	m_dead = true;
}