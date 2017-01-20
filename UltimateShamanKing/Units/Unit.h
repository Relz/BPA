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
	void Init(sf::Vector2f startPosition, float movementSpeed, float upSpeed, float downSpeed, float gravity);
	void Draw(sf::RenderTarget &target) const;
	void SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom);
	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f & position);
	void Move(const sf::Vector2f & offset);
	float GetWidth() const;
	float GetHeight() const;
	float GetTop() const;
	float GetLeft() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetMovement() const;
	bool IsStaying() const;

	virtual void MoveProcess(const std::vector<TmxObject> & collisionBlocks) = 0;
	bool IsAlive() const;
	virtual void Die();

	float movementSpeed = 0;
	float upSpeed = 0;
	float downSpeed = 0;
	float startDownSpeed = 0;
	float gravity = 0;
	bool jumping = false;
	bool attacking = false;
	sf::Vector2f direction;
	Collision collision;

protected:
	void UpdateCollision(const std::vector<TmxObject> & collisionBlocks);
	bool IsAbyssOnSide(const std::vector<TmxObject> & collisionBlocks) const;
	void MoveX();
	void Gravity();

	sf::Sprite m_sprite;
	int m_startSpriteOffsetLeft = 0;
	int m_startSpriteOffsetTop = 0;
	int m_startSpriteWidth = 0;
	int m_startSpriteHeight = 0;

	float m_width = 0;
	float m_height = 0;

private:
	Collision GetCollision(const std::vector<TmxObject> & collisionBlocks,
						   float unitLeft,
						   float unitTop,
						   float & out_collisionBlockTop,
						   float & out_collisionBlockBottom) const;
	void GetCollision(const TmxObject & collisionBlock,
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
						   Collision & out_collision) const;
	sf::Texture m_texture;
	bool m_dead = false;

};


#endif //ULTIMATE_SHAMAN_KING_UNIT_H
