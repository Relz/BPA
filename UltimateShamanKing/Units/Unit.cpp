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
    m_startOffsetLeft = playerSpriteRect.left;
    m_startOffsetTop = playerSpriteRect.top;
    m_startWidth = playerSpriteRect.width;
    m_startHeight = playerSpriteRect.height;
    m_sprite.setScale(zoom, zoom);
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

sf::IntRect CUnit::GetRect() const
{
    return sf::IntRect(static_cast<int>(GetLeft()), static_cast<int>(GetTop()), static_cast<int>(GetWidth()), static_cast<int>(GetHeight()));
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

void CUnit::UpdateCollision(const std::vector<TmxObject> & tiles)
{
    collision = Collision();
    sf::IntRect unitRect = GetRect();
    sf::Vector2f unitMovement = GetMovement();

    const float futureUnitTopY = unitRect.top + unitMovement.y;
    const float futureUnitBottomY = futureUnitTopY + unitRect.height;
    const float futureUnitLeftX = unitRect.left + unitMovement.x;
    const float futureUnitRightX = futureUnitLeftX + unitRect.width;

    const float unitTopY = unitRect.top;
    const float unitBottomY = unitTopY + unitRect.height;
    const float unitLeftX = unitRect.left;
    const float unitRightX = unitLeftX + unitRect.width;

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
            bool playerPlacesInOneHorizontalWithTile = DoesObjectsPlacesInOneHorizontal(unitTopY, unitBottomY, tileTopY, tileBottomY);
            bool isLeftCollision = futureUnitLeftX <= tileRightX && futureUnitRightX >= tileRightX && unitLeftX >= tileRightX;
            bool isRightCollision = futureUnitRightX >= tileLeftX && futureUnitLeftX <= tileLeftX && unitRightX <= tileLeftX;

            if (playerPlacesInOneHorizontalWithTile && (isLeftCollision || isRightCollision))
            {
                collision.left = isLeftCollision;
                collision.right = isRightCollision;
                XCollisionProcessed = true;
            }
        }

        if (!YCollisionProcessed)
        {
            bool playerPlacesInOneVerticalWithTile = DoesObjectsPlacesInOneVertical(unitLeftX, unitRightX, tileLeftX, tileRightX);
            bool isTopCollision = futureUnitTopY <= tileBottomY && futureUnitBottomY >= tileBottomY/* && playerTopY >= tileBottomY*/;
            bool isBottomCollision = futureUnitBottomY >= tileTopY && futureUnitTopY <= tileTopY/* && playerBottomY < tileTopY*/;

            if (playerPlacesInOneVerticalWithTile && (isTopCollision || isBottomCollision))
            {
                collision.top = isTopCollision;
                collision.bottom = isBottomCollision;
                YCollisionProcessed = true;
                if (collision.top && !attacking)
                {
                    SetPosition(GetPosition().x, tileBottomY + 1);
                }
                if (collision.bottom && downSpeed > 0 && !attacking)
                {
                    SetPosition(GetPosition().x, tileTopY - GetHeight() + downSpeed);
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

sf::Vector2f CUnit::GetMovement() const
{
    return Round({direction.x * movementSpeed, direction.y * downSpeed});
}

bool CUnit::IsStaying() const
{
    return (direction.x == 0 && direction.y == 0);
}