// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_UNIT_H
#define ULTIMATE_SHAMAN_KING_UNIT_H

#include "../TmxLevel.h"

struct Collision
{
	bool top = false;
	bool right = false;
	bool bottom = false;
	bool left = false;
};

class CUnit
{
public:
	void Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity, float dyingTime);
	void Draw(sf::RenderTarget &target) const;
	void SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom);
	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f & position);
	void SetImpuls(float x, float y);
	void Move(const sf::Vector2f & offset);
	float GetWidth() const;
	float GetSpriteWidth() const;
	float GetHeight() const;
	float GetSpriteHeight() const;
	float GetTop() const;
	float GetLeft() const;
	sf::IntRect GetRect() const;
	sf::IntRect GetFutureRect() const;
	sf::IntRect GetSpriteRect() const;
	sf::IntRect GetFutureSpriteRect() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetMovement() const;
	sf::Vector2f GetDirection() const;
	float GetDyingTimeSec() const;
	float GetDyingClockSec() const;
	float GetUpSpeed() const;
	bool IsStaying() const;
	bool IsAlive() const;
	bool DoesAttacking() const;
	bool DoesJumping() const;

	virtual void Process(const std::vector<TmxObject> & collisionBlocks) = 0;
	virtual void Die();

	static void GetCollision(const sf::IntRect & objectRect,
	                         const sf::IntRect & unitRect,
	                         const sf::IntRect & unitFutureRect,
	                         float unitDirectionX,
	                         float playerWidth,
	                         float & out_collisionBlockTop,
	                         float & out_collisionBlockBottom,
	                         Collision & out_collision);
	static bool DoesObjectsPlacesInOneVertical(float object1LeftX, float object1RightX, float object2LeftX, float object2RightX);
	static bool DoesObjectsPlacesInOneHorizontal(float object1TopY, float object1BottomY, float object2TopY, float object2BottomY);

protected:
	void UpdateCollision(const std::vector<TmxObject> & collisionBlocks);
	bool IsAbyssOnSide(const std::vector<TmxObject> & collisionBlocks) const;
	void MoveX();
	void Gravity();
	Collision GetCollision(const std::vector<TmxObject> & collisionBlocks,
	                       float unitLeft,
	                       float unitTop,
	                       float & out_collisionBlockTop,
	                       float & out_collisionBlockBottom) const;

	sf::Sprite m_sprite;

	int m_startSpriteOffsetLeft = 0;
	int m_startSpriteOffsetTop = 0;
	int m_startSpriteWidth = 0;
	int m_startSpriteHeight = 0;

	float movementSpeed = 0;
	float upSpeed = 0;
	float downSpeed = 0;
	float startDownSpeed = 0;
	float gravity = 0;
	bool jumping = false;
	sf::Vector2f direction;
	Collision collision;

	bool m_attacking = false;

	sf::Vector2f m_lastDirection;

	sf::Clock m_dyingClock;

private:
	sf::Texture m_texture;

	float m_width = 0;
	float m_height = 0;

	bool m_dead = false;
	float m_dyingTimeSec = 0;

};


#endif //ULTIMATE_SHAMAN_KING_UNIT_H
