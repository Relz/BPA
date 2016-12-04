#include "stdafx.h"
#include "Drawable.h"

CDrawable::CDrawable(sf::Shape *model)
    : m_model(model)
{
}

sf::Shape const* CDrawable::getModel() const
{
    return m_model;
}