// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
		: m_SPLine(sf::Color::Blue)
{
}

void CPlayer::Init(const std::wstring & name,
				sf::Vector2f startPosition,
				float movementSpeed,
				float upSpeed,
				float downSpeed,
				float gravity,
				float dyingTimeSec,
				size_t HP,
				size_t SP,
				size_t strength,
				size_t skillCount)
{
	this->m_SP = SP;
	this->m_skillCount = skillCount;
	m_SPLine.SetPoints(SP);
	m_shield.SetSprite("../res/Images/Skills/shield.png", 0.6);
	CUnit::Init(name, startPosition, movementSpeed, upSpeed, downSpeed, gravity, dyingTimeSec, HP, strength);
}

void CPlayer::Process(const std::vector<TmxObject> & collisionBlocks)
{
	if (IsAlive())
	{
		UpdateDirection();
		UpdateSkillUsing();
		if (IsWithSpirit() && m_spReducingForSpiritClock.getElapsedTime().asSeconds() > 1)
		{
			m_spReducingForSpiritClock.restart();
			ReduceSP(1);
		}
		if (IsWithShield() && m_spReducingForShieldClock.getElapsedTime().asSeconds() > 1)
		{
			m_spReducingForShieldClock.restart();
			ReduceSP(1);
		}
		if (GetSP() == 0)
		{
			SetShield(false);
			SetSpirit(false);
		}
		if (DoesAttack() && !IsWithShield() && m_attackingClock.getElapsedTime().asSeconds() > 0.5 && !IsAttacking())
		{
			m_attacking = true;
			m_attackingClock.restart();
		}
		if (m_attackingClock.getElapsedTime().asSeconds() > 0.5)
		{
			m_attacking = false;
		}
		if (m_usingCloudstrikeClock.getElapsedTime().asSeconds() > 0.5)
		{
			SetUsingCloudstrike(false);
		}
		UpdateCollision(collisionBlocks);
		if ((GetDirection().x > 0 && !collision.right) || (GetDirection().x < 0 && !collision.left))
		{
			MoveX();
		}
		bool canJump = !IsJumping() && GetDirection().y == -1 && !collision.top && !IsAttacking();
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
	Animate(m_animationClock);
}

void CPlayer::Draw(sf::RenderTarget & target)
{
	m_SPLine.SetPoints(GetSP());
	m_SPLine.Draw(target);
	CUnit::Draw(target);
	if (IsWithShield())
	{
		float offsetX = (GetLastDirection().x == 1) ? 40 : 0;
		m_shield.SetPosition({GetPosition().x + offsetX, GetPosition().y - GetHeight() / 1.5f});
		m_shield.Draw(target, GetLastDirection().x);
	}
}

void CPlayer::SetPosition(float x, float y)
{
	float SPLinePositionX = x + GetWidth() / 2;
	float SPLinePositionY = y - 40;
	m_SPLine.SetPosition(SPLinePositionX, SPLinePositionY);
	CUnit::SetPosition(x, y);
}

void CPlayer::SetPosition(const sf::Vector2f & position)
{
	SetPosition(position.x, position.y);
}

void CPlayer::MoveX()
{
	m_SPLine.Move(GetMovement().x, 0);
	CUnit::MoveX();
}

void CPlayer::Gravity()
{
	m_SPLine.Move(0, downSpeed);
	CUnit::Gravity();
}

void CPlayer::ReduceSP(float value)
{
	m_SP = (GetSP() > value) ? GetSP() - value : 0;
}

void CPlayer::IncreaseSP(float value)
{
	m_SP += (GetSP() + value > 100) ? 100 - GetSP() : value;
}

float CPlayer::GetSP() const
{
	return m_SP;
}

int CPlayer::GetUsingSkill() const
{
	return m_usingSkill;
}

void CPlayer::SetSpirit(bool isWithSpirit)
{
	m_isWithSpirit = isWithSpirit;
}

void CPlayer::SetShield(bool isWithShield)
{
	m_isWithShield = isWithShield;
}

bool CPlayer::IsWithSpirit() const
{
	return m_isWithSpirit;
}

bool CPlayer::IsUsingCloudstrike() const
{
	return m_isUsingCloudstrike;
}

bool CPlayer::IsWithShield() const
{
	return m_isWithShield;
}

void CPlayer::UseSkill(const std::string skillName, float spReduce)
{
	if (skillName == SKILL_SPIRIT)
	{
		if (!IsUsingCloudstrike())
		{
			if (IsWithSpirit())
			{
				SetShield(false);
				SetSpirit(false);
			}
			else if (GetSP() >= spReduce)
			{
				SetSpirit(true);
				ReduceSP(spReduce);
			}
		}
	}
	else if (skillName == SKILL_CLOUDSTRIKE)
	{
		if (!IsWithShield() && !IsUsingCloudstrike() && !IsAttacking() && GetSP() >= spReduce)
		{
			SetUsingCloudstrike(true);
			ReduceSP(spReduce);
			m_usingCloudstrikeClock.restart();
		}
	}
	else if (skillName == SKILL_SHIELD)
	{
		if (!IsUsingCloudstrike() && !IsAttacking())
		{
			if (IsWithShield())
			{
				SetShield(false);
			}
			else if (GetSP() >= spReduce)
			{
				SetShield(true);
				ReduceSP(spReduce);
			}
		}
	}
}

void CPlayer::UpdateDirection()
{
	sf::Vector2f direction;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
	{
		direction.y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && !IsAttacking() && !IsUsingCloudstrike())
	{
		direction.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6) && !IsAttacking() && !IsUsingCloudstrike())
	{
		direction.x = 1;
	}
	SetDirection(direction);
}

void CPlayer::UpdateSkillUsing()
{
	int firstKeyCode = sf::Keyboard::Num1;
	static bool canUseSkill = true;
	bool someSkillIsPressed = false;
	m_usingSkill = -1;

	for (size_t i = 0; i < GetSkillCount(); ++i)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(firstKeyCode + i)))
		{
			if (canUseSkill)
			{
				m_usingSkill = static_cast<int>(i);
				canUseSkill = false;
			}
			someSkillIsPressed = true;
		}
	}

	if (!someSkillIsPressed)
	{
		canUseSkill = true;
	}
}

void CPlayer::Animate(sf::Clock & animationClock)
{
	float deltaSec = animationClock.getElapsedTime().asSeconds();
	if (deltaSec > 0.1 && IsAlive())
	{
		if (IsAttacking())
		{
			UpdateAttackingSprite();
			animationClock.restart();
		}
		else if (IsUsingCloudstrike())
		{
			UpdateUsingCloudstrikeSprite();
			animationClock.restart();
		}
		else if (IsJumping())
		{
			UpdateJumpingSprite();
		}
		else if (!IsStaying())
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
}

void CPlayer::UpdateStayingSprite()
{
	m_currentMovingSprite = 0;
	m_currentAttackingSprite = 0;
	m_currentUsingCloudstrikeSprite = 0;
	m_currentStayingSprite = (m_currentStayingSprite == 3) ? 0 : m_currentStayingSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startSpriteWidth;
	textureRect.top = m_startSpriteOffsetTop;
	m_modelSprite.setOrigin(0, 0);
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}

	switch (m_currentStayingSprite)
	{
		case 0:
			textureRect.height = m_startSpriteHeight;
			textureRect.left = offsetLeft + 6;
			textureRect.top = m_startSpriteOffsetTop;
			break;
		case 1:
			textureRect.height = m_startSpriteHeight + 1;
			textureRect.left = offsetLeft + 39;
			textureRect.top = m_startSpriteOffsetTop + 1;
			break;
		case 2:
			textureRect.height = m_startSpriteHeight + 2;
			textureRect.left = offsetLeft + 72;
			textureRect.top = m_startSpriteOffsetTop + 2;
			break;
		case 3:
			textureRect.height = m_startSpriteHeight + 1;
			textureRect.left = offsetLeft + 39;
			textureRect.top = m_startSpriteOffsetTop + 1;
			break;
		default:
			break;
	}
	m_modelSprite.setTextureRect(textureRect);
}

void CPlayer::UpdateMovingSprite()
{
	m_currentStayingSprite = 0;
	m_currentAttackingSprite = 0;
	m_currentUsingCloudstrikeSprite = 0;
	m_currentMovingSprite = (m_currentMovingSprite == 5) ? 0 : m_currentMovingSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startSpriteWidth;
	textureRect.height = m_startSpriteHeight;
	textureRect.top = 91;
	m_modelSprite.setOrigin(0, 0);
	if (GetLastDirection().x == -1)
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
	m_modelSprite.setTextureRect(textureRect);
}

void CPlayer::UpdateJumpingSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = 0;
	m_currentAttackingSprite = 0;
	m_currentUsingCloudstrikeSprite = 0;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startSpriteWidth;
	textureRect.height = m_startSpriteHeight;
	textureRect.top = 149;
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
	}

	textureRect.left = (downSpeed > 0) ? offsetLeft + 156 : offsetLeft + 100;
	m_modelSprite.setTextureRect(textureRect);
}

void CPlayer::UpdateAttackingSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = 0;
	m_currentUsingCloudstrikeSprite = 0;
	m_currentAttackingSprite = (m_currentAttackingSprite == 4) ? 0 : m_currentAttackingSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.width = m_startSpriteWidth;
	textureRect.height = m_startSpriteHeight;
	m_modelSprite.setOrigin(0, 0);
	switch (m_currentAttackingSprite)
	{
		case 0:
			textureRect.top = 91;
			textureRect.left = 412;
			break;
		case 1:
			textureRect.width = 60;
			textureRect.top = 90;
			textureRect.left = 445;
			break;
		case 2:
			textureRect.width = 70;
			textureRect.top = 89;
			textureRect.left = 511;
			break;
		case 3:
			textureRect.width = 70;
			textureRect.top = 88;
			textureRect.left = 590;
			break;
		case 4:
			textureRect.width = 70;
			textureRect.top = 130;
			textureRect.left = 629;
			break;
		default:
			break;
	}
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
		m_modelSprite.setOrigin(-textureRect.width - m_startSpriteWidth, 0);
	}
	textureRect.left += offsetLeft;
	m_modelSprite.setTextureRect(textureRect);
}

void CPlayer::UpdateUsingCloudstrikeSprite()
{
	m_currentStayingSprite = 0;
	m_currentMovingSprite = 0;
	m_currentAttackingSprite = 0;
	m_currentUsingCloudstrikeSprite = (m_currentUsingCloudstrikeSprite == 9) ? 0 : m_currentUsingCloudstrikeSprite + 1;
	sf::IntRect textureRect = m_modelSprite.getTextureRect();
	int offsetLeft = 0;
	textureRect.height = m_startSpriteHeight;
	switch (m_currentUsingCloudstrikeSprite)
	{
		case 0:
			m_modelSprite.setOrigin(26, 0);
			textureRect.width = 53;
			textureRect.top = 256;
			textureRect.left = 0;
			break;
		case 1:
			m_modelSprite.setOrigin(19, 0);
			textureRect.width = 46;
			textureRect.top = 256;
			textureRect.left = 58;
			break;
		case 2:
			m_modelSprite.setOrigin(24, 0);
			textureRect.width = 56;
			textureRect.top = 268;
			textureRect.left = 106;
			break;
		case 3:
			m_modelSprite.setOrigin(6, 0);
			textureRect.width = 79;
			textureRect.top = 273;
			textureRect.left = 170;
			break;
		case 4:
			m_modelSprite.setOrigin(0, 0);
			textureRect.width = 69;
			textureRect.top = 270;
			textureRect.left = 249;
			break;
		case 5:
			m_modelSprite.setOrigin(10, 0);
			textureRect.width = 66;
			textureRect.top = 272;
			textureRect.left = 318;
			break;
		case 6:
			m_modelSprite.setOrigin(4, 0);
			textureRect.width = 60;
			textureRect.top = 271;
			textureRect.left = 384;
			break;
		case 7:
			m_modelSprite.setOrigin(4, 0);
			textureRect.width = 44;
			textureRect.top = 271;
			textureRect.left = 444;
			break;
		case 8:
			m_modelSprite.setOrigin(0, 0);
			textureRect.width = 43;
			textureRect.top = 271;
			textureRect.left = 488;
			break;
		case 9:
			m_modelSprite.setOrigin(0, 0);
			textureRect.width = 43;
			textureRect.top = 271;
			textureRect.left = 531;
			break;
		default:
			break;
	}
	if (GetLastDirection().x == -1)
	{
		offsetLeft = textureRect.width;
		textureRect.width = -textureRect.width;
		m_modelSprite.setOrigin(-textureRect.width - m_startSpriteWidth - m_modelSprite.getOrigin().x, 0);
	}
	textureRect.left += offsetLeft;
	m_modelSprite.setTextureRect(textureRect);
}

bool CPlayer::DoesAttack() const
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !IsUsingCloudstrike();
}

size_t CPlayer::GetSkillCount() const
{
	return m_skillCount;
}

void CPlayer::SetUsingCloudstrike(bool value)
{
	m_isUsingCloudstrike = value;
}
