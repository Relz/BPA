// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_UNIT_H
#define ULTIMATE_SHAMAN_KING_UNIT_H

#include "../TmxLevel.h"
#include "../Line.h"

struct Collision
{
	bool top = false;
	bool right = false;
	bool bottom = false;
	bool left = false;

	bool Any()
	{
		return top || right || bottom || left;
	}
};

class CUnit
{
public:
	CUnit();
	void Init(const std::wstring & name,
	          sf::Vector2f startPosition,
	          float movementSpeed,
	          float upSpeed,
	          float downSpeed,
	          float gravity,
	          float dyingTimeSec,
	          size_t HP,
	          size_t strength);
	virtual void Draw(sf::RenderTarget & target) const;
	void SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom);
	void SetSprite(const std::string & spritePath, float zoom);
	void SetDialogAvatarNormal(const std::string & dialogAvatarPath, float zoom);
	void SetDialogAvatarAngry(const std::string & dialogAvatarPath, float zoom);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f & position);
	void SetImpuls(float x, float y);
	void Move(const sf::Vector2f & offset);
	std::wstring GetName() const;
	float GetWidth() const;
	float GetSpriteWidth() const;
	float GetHeight() const;
	float GetSpriteHeight() const;
	float GetTop() const;
	float GetLeft() const;
	sf::FloatRect GetRect() const;
	sf::FloatRect GetFutureRect() const;
	sf::FloatRect GetSpriteRect() const;
	sf::FloatRect GetFutureSpriteRect() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetMovement() const;
	sf::Vector2f GetDirection() const;
	sf::Vector2f GetLastDirection() const;
	float GetDyingTimeSec() const;
	float GetDyingClockSec() const;
	float GetUpSpeed() const;
	float GetHP() const;
	float GetStrength() const;
	bool IsStaying() const;
	bool IsAlive() const;
	bool IsAttacking() const;
	bool IsJumping() const;
	void ReduceHP(float value);
	void Show();
	void Hide();
	bool IsVisible() const;
	void TurnAround();
	void TurnLeft();
	void TurnRight();
	void Stop();
	sf::Sprite * GetDialogAvatarNormal();
	sf::Sprite * GetDialogAvatarAngry();

	virtual void Process(const std::vector<TmxObject> & collisionBlocks) = 0;
	virtual void Die();

	static void GetCollision(const sf::FloatRect & objectRect,
	                         const sf::FloatRect & unitRect,
	                         const sf::FloatRect & unitFutureRect,
	                         float unitDirectionX,
	                         float playerWidth,
	                         float & out_collisionBlockTop,
	                         float & out_collisionBlockBottom,
	                         Collision & out_collision);

	static void GetCollision(const sf::FloatRect & objectRect,
	                         const sf::FloatRect & unitRect,
	                         const sf::FloatRect & unitFutureRect,
	                         float unitDirectionX,
	                         float playerWidth,
	                         Collision & out_collision);
	static bool DoesObjectsPlacesInOneVertical(float object1LeftX, float object1RightX, float object2LeftX, float object2RightX);
	static bool DoesObjectsPlacesInOneHorizontal(float object1TopY, float object1BottomY, float object2TopY, float object2BottomY);

protected:
	void UpdateCollision(const std::vector<TmxObject> & collisionBlocks);
	bool IsAbyssOnSide(const std::vector<TmxObject> & collisionBlocks) const;
	virtual void MoveX();
	virtual void Gravity();
	Collision GetCollision(const std::vector<TmxObject> & collisionBlocks,
	                       float unitLeft,
	                       float unitTop,
	                       float & out_collisionBlockTop,
	                       float & out_collisionBlockBottom) const;
	Collision GetCollision(const std::vector<TmxObject> & collisionBlocks, float unitLeft, float unitTop) const;
	void SetDirection(const sf::Vector2f & value);

	sf::Sprite m_modelSprite;
	sf::Sprite m_avatarNormalSprite;
	sf::Sprite m_avatarAngrySprite;

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
	Collision collision;

	bool m_attacking = false;

	sf::Clock m_dyingClock;

	float strength = 0;

	bool m_visible = true;

private:
	void SetTexture(sf::Texture & texture, const std::string & texturePath);

	std::wstring m_name;

	sf::Texture m_modelTexture;
	sf::Texture m_avatarNormalTexture;
	sf::Texture m_avatarAngryTexture;

	CLine m_HPLine;

	float m_HP = 100;

	float m_width = 0;
	float m_height = 0;

	bool m_dead = false;
	float m_dyingTimeSec = 0;

	sf::Vector2f m_direction = {1, 0};
	sf::Vector2f m_lastDirection = {1, 0};

};


#endif //ULTIMATE_SHAMAN_KING_UNIT_H
