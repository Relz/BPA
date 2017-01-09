#ifndef ULTIMATE_SHAMAN_KING_PLAYER_H
#define ULTIMATE_SHAMAN_KING_PLAYER_H

#include "stdafx.h"
#include "TmxLevel.h"

struct Collision
{
	bool top = false;
	bool right = false;
	bool bottom = false;
	bool left = false;
};

class CPlayer
{
public:
	void Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity);
	void Draw(sf::RenderTarget &target) const;
	void SetSprite(const std::string & spriteName, const sf::IntRect & playerSpriteRect, float zoom);
	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f & position);
	void Move(const sf::Vector2f & offset);
	void MoveProcess(const std::vector<TmxObject> & collisionBlocks, sf::Clock & clock);
	float GetWidth() const;
	float GetHeight() const;
	float GetTop() const;
	float GetLeft() const;
	sf::IntRect GetRect() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetMovement() const;
	bool IsStaying() const;

	float movementSpeed = 0;
	float upSpeed = 0;
	float downSpeed = 0;
	float startDownSpeed = 0;
	float gravity = 0;
	bool jumping = false;
	sf::Vector2f direction;
	Collision collision;

private:
	void MoveX();
	void UpdateDirection();
	void Gravity();
	void Animate(sf::Clock & clock);
	void UpdateStayingSprite();
	void UpdateMovingSprite();
	void UpdateJumpingSprite();
	void UpdateCollision(const std::vector<TmxObject> & tiles);

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	int m_startOffsetLeft = 0;
	int m_startOffsetTop = 0;
	int m_startWidth = 0;
	int m_startHeight = 0;

	size_t m_currentStayingSprite = 0;
	size_t m_currentMovingSprite = 0;

	sf::Vector2f m_lastDirection;
};


#endif //ULTIMATE_SHAMAN_KING_PLAYER_H
