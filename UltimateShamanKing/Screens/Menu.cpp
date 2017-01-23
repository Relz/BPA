// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "Menu.h"

void CMenu::AddMenuItem(MenuItem * menuItem)
{
	m_menuItems.push_back(menuItem);
}

void CMenu::SetPosition(const sf::Vector2f &position)
{
	m_position = position;
	UpdateMenuItemsPosition();
}

void CMenu::Draw(sf::RenderTarget &target)
{
	if (!m_hidden)
	{
		for (MenuItem * menuItem : m_menuItems)
		{
			menuItem->Draw(target);
		}
	}
}

void CMenu::UpdateMenuItemsPosition()
{
	for (size_t i = 0; i < m_menuItems.size(); ++i)
	{
		MenuItem * menuItem = m_menuItems.at(i);
		menuItem->SetPosition(sf::Vector2f(m_position.x, m_position.y + i * menuItem->GetCharacterSize() * 2));
	}
}

void CMenu::Hide()
{
	m_hidden = true;
}

void CMenu::Show()
{
	m_hidden = false;
}

static bool IsDotInRect(const sf::Vector2i & dot, const sf::FloatRect & rect)
{
	float rectRight = rect.left + rect.width;
	float rectBottom = rect.top + rect.height;
	return dot.x > rect.left && dot.x < rectRight && dot.y > rect.top && dot.y < rectBottom;
}

void CMenu::Process(sf::RenderWindow & window)
{
	if (IsVisible())
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		for (MenuItem * menuItem : m_menuItems)
		{
			sf::FloatRect menuItemRect = menuItem->m_text.getGlobalBounds();
			if (IsDotInRect(mousePosition, menuItemRect))
			{
				menuItem->SetFocus(true);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					menuItem->SetClicked(true);
				}
			}
			else
			{
				menuItem->SetFocus(false);
			}
		}
	}
}

bool CMenu::IsVisible() const
{
	return !m_hidden;
}
