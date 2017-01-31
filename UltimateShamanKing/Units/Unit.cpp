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

void CUnit::GetCollision(const sf::FloatRect & objectRect,
                         const sf::FloatRect & unitRect,
                         const sf::FloatRect & unitFutureRect,
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

void CUnit::GetCollision(const sf::FloatRect & objectRect,
                         const sf::FloatRect & unitRect,
                         const sf::FloatRect & unitFutureRect,
                         float unitDirectionX,
                         float playerWidth,
                         Collision & out_collision)
{
	float out_collisionBlockTop = 0;
	float out_collisionBlockBottom = 0;
	GetCollision(objectRect, unitRect, unitFutureRect, unitDirectionX, playerWidth, out_collisionBlockTop, out_collisionBlockBottom, out_collision);
}

void CUnit::Init(const std::wstring & name,
                 sf::Vector2f startPosition,
                 float movementSpeed,
                 float upSpeed,
                 float downSpeed,
                 float gravity,
                 float dyingTimeSec,
                 size_t HP,
                 size_t strength)
{
	SetPosition(startPosition);
	this->m_name = name;
	this->m_dead = false;
	this->movementSpeed = movementSpeed;
	this->upSpeed = upSpeed;
	this->startDownSpeed = downSpeed;
	this->gravity = gravity;
	this->m_dyingTimeSec = dyingTimeSec;
	this->HP = HP;
	this->strength = strength;
	m_HPLine.SetHP(HP);
	Show();
}

void CUnit::Draw(sf::RenderTarget & target) const
{
	if (IsVisible())
	{
		m_HPLine.Draw(target);
		target.draw(m_modelSprite);
	}
}

void CUnit::SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom)
{
	m_modelSprite.setTextureRect(sf::IntRect(playerSpriteRect.left, playerSpriteRect.top, playerSpriteRect.width, playerSpriteRect.height));
	SetSprite(spritePath, zoom);
}

void CUnit::SetSprite(const std::string & spritePath, float zoom)
{
	SetTexture(m_modelTexture, spritePath);
	m_modelSprite.setTexture(m_modelTexture);
	m_modelSprite.setScale(zoom, zoom);
	m_width = m_modelSprite.getGlobalBounds().width;
	m_height = m_modelSprite.getGlobalBounds().height;
	m_startSpriteOffsetLeft = m_modelSprite.getTextureRect().left;
	m_startSpriteOffsetTop = m_modelSprite.getTextureRect().top;
	m_startSpriteWidth = m_modelSprite.getTextureRect().width;
	m_startSpriteHeight = m_modelSprite.getTextureRect().height;
}

void CUnit::SetDialogAvatarNormal(const std::string & dialogAvatarNormalPath, float zoom)
{
	SetTexture(m_avatarNormalTexture, dialogAvatarNormalPath);
	m_avatarNormalSprite.setTexture(m_avatarNormalTexture);
	m_avatarNormalSprite.setScale(zoom, zoom);
	m_avatarNormalSprite.setPosition(0, 0);
}

void CUnit::SetDialogAvatarAngry(const std::string & dialogAvatarAngryPath, float zoom)
{
	SetTexture(m_avatarAngryTexture, dialogAvatarAngryPath);
	m_avatarAngrySprite.setTexture(m_avatarAngryTexture);
	m_avatarAngrySprite.setScale(zoom, zoom);
	m_avatarAngrySprite.setPosition(0, 0);
}

void CUnit::SetPosition(float x, float y)
{
	float HPLinePositionX = x + GetWidth() / 2;
	float HPLinePositionY = y - 50;
	m_HPLine.SetPosition(HPLinePositionX, HPLinePositionY);
	m_modelSprite.setPosition(x, y);
}

void CUnit::SetPosition(const sf::Vector2f & position)
{
	SetPosition(position.x, position.y);
}

void CUnit::SetImpuls(float x, float y)
{
	jumping = true;
	downSpeed -= y;
	if (x > 0)
	{
		TurnRight();
	}
	else if (x < 0)
	{
		TurnLeft();
	}
}

void CUnit::MoveX()
{
	m_HPLine.Move(GetMovement().x, 0);
	m_modelSprite.move(GetMovement().x, 0);
}

void CUnit::Move(const sf::Vector2f & offset)
{
	m_modelSprite.move(offset);
}

std::wstring CUnit::GetName() const
{
	return m_name;
}

sf::Vector2f CUnit::GetPosition() const
{
	return m_modelSprite.getPosition();
}

void CUnit::Gravity()
{
	m_HPLine.Move(0, downSpeed);
	m_modelSprite.move(0, downSpeed);
}

float CUnit::GetWidth() const
{
	return m_width;
}

float CUnit::GetSpriteWidth() const
{
	return m_modelSprite.getGlobalBounds().width;
}

float CUnit::GetHeight() const
{
	return m_modelSprite.getGlobalBounds().height;
}

float CUnit::GetSpriteHeight() const
{
	return m_height;
}

float CUnit::GetTop() const
{
	return m_modelSprite.getPosition().y;
}

float CUnit::GetLeft() const
{
	return m_modelSprite.getPosition().x;
}

sf::FloatRect CUnit::GetRect() const
{
	return sf::FloatRect(GetLeft(),
	                   GetTop(),
	                   GetWidth(),
	                   GetHeight());
}

sf::FloatRect CUnit::GetFutureRect() const
{
	sf::Vector2f unitMovement = GetMovement();
	return sf::FloatRect(GetLeft() + unitMovement.x,
	                   GetTop() + unitMovement.y,
	                   GetWidth(),
	                   GetHeight());
}

sf::FloatRect CUnit::GetSpriteRect() const
{
	return sf::FloatRect(GetLeft(),
	                   GetTop(),
	                   GetSpriteWidth(),
	                   GetSpriteHeight());
}

sf::FloatRect CUnit::GetFutureSpriteRect() const
{
	sf::Vector2f unitMovement = GetMovement();
	return sf::FloatRect(GetLeft() + unitMovement.x,
	                   GetTop() + unitMovement.y,
	                   GetSpriteWidth(),
	                   GetSpriteHeight());
}

sf::Vector2f CUnit::GetMovement() const
{
	return sf::Vector2f(roundf(m_direction.x * movementSpeed), roundf(m_direction.y * downSpeed));
}

sf::Vector2f CUnit::GetDirection() const
{
	return m_direction;
}

sf::Vector2f CUnit::GetLastDirection() const
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

float CUnit::GetHP() const
{
	return HP;
}

float CUnit::GetStrength() const
{
	return strength;
}

bool CUnit::IsStaying() const
{
	return (GetDirection().x == 0 && GetDirection().y == 0);
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

void CUnit::ReduceHP(float value)
{
	HP = (HP > value) ? HP - value : 0;
	m_HPLine.SetHP(HP);
	if (HP == 0)
	{
		Die();
	}
}

void CUnit::Show()
{
	m_visible = true;
}

void CUnit::Hide()
{
	m_visible = false;
}

bool CUnit::IsVisible() const
{
	return m_visible;
}

void CUnit::TurnAround()
{
	sf::Vector2f direction = m_direction;
	direction.x = -m_direction.x;
	SetDirection(direction);
}

void CUnit::TurnLeft()
{
	sf::Vector2f direction = m_direction;
	direction.x = -1;
	SetDirection(direction);
}

void CUnit::TurnRight()
{
	sf::Vector2f direction = m_direction;
	direction.x = 1;
	SetDirection(direction);
}

void CUnit::Stop()
{
	m_direction.x = 0;
}

sf::Sprite * CUnit::GetDialogAvatarNormal()
{
	return & m_avatarNormalSprite;
}

sf::Sprite * CUnit::GetDialogAvatarAngry()
{
	return & m_avatarAngrySprite;
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
	bool isLeftAbyss = !GetCollision(collisionBlocks, GetLeft() - m_width, GetTop()).bottom;
	bool isRightAbyss = !GetCollision(collisionBlocks, GetLeft() + m_width, GetTop()).bottom;
	return isLeftAbyss || isRightAbyss;
}

Collision CUnit::GetCollision(const std::vector<TmxObject> & collisionBlocks,
                              float unitLeft,
                              float unitTop,
                              float & out_collisionBlockTop,
                              float & out_collisionBlockBottom) const
{
	Collision result;

	sf::FloatRect unitRect = {unitLeft, unitTop, GetWidth(), GetHeight()};

	sf::Vector2f unitMovement = GetMovement();
	float unitFutureLeft = unitLeft + unitMovement.x;
	float unitFutureTop = unitTop + unitMovement.y;

	sf::FloatRect unitFutureRect = {unitFutureLeft, unitFutureTop, GetWidth(), GetHeight()};

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

Collision CUnit::GetCollision(const std::vector<TmxObject> & collisionBlocks, float unitLeft, float unitTop) const
{
	float collisionBlockTop = 0;
	float collisionBlockBottom = 0;
	return GetCollision(collisionBlocks, unitLeft, unitTop, collisionBlockTop, collisionBlockBottom);
}

void CUnit::Die()
{
	m_dyingClock.restart();
	m_dead = true;
}

void CUnit::SetTexture(sf::Texture & texture, const std::string & texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		throw std::invalid_argument("\"" + texturePath + "\" not found");
	}
}

void CUnit::SetDirection(const sf::Vector2f & value)
{
	m_direction = value;
	if (m_direction.x == 1 || m_direction.x == -1)
	{
		m_lastDirection.x = m_direction.x;
	}
}
