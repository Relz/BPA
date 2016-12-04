#include "stdafx.h"
#include "Yoh.h"

CYoh::CYoh(sf::Vector2f startPos)
        : CDrawable(new sf::RectangleShape)
{
    static_cast<sf::RectangleShape *>(m_model)->setPosition(startPos);
    static_cast<sf::RectangleShape *>(m_model)->setSize(sf::Vector2f(50, 50));
    static_cast<sf::RectangleShape *>(m_model)->setFillColor(sf::Color::Blue);
}

void CYoh::update()
{
    float newPosX = m_model->getPosition().x;
    float newPosY = m_model->getPosition().y;

    if (up)
    {
        newPosY -= YOH_SPEED_Y;
        m_model->setPosition(newPosX, newPosY);
    }
    if (right)
    {
        newPosX += YOH_SPEED_X;
        m_model->setPosition(newPosX, newPosY);
    }
    if (down)
    {
        newPosY += YOH_SPEED_Y;
        m_model->setPosition(newPosX, newPosY);
    }
    if (left)
    {
        newPosX -= YOH_SPEED_X;
        m_model->setPosition(newPosX, newPosY);
    }
}