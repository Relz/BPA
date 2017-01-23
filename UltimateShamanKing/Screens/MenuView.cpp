// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "../stdafx.h"
#include "MenuView.h"

CMenuView::CMenuView(const sf::Vector2u & windowSize)
{
	m_windowSize = windowSize;
	AddBackground("../res/Images/Menu/menu_background0.png", {m_windowSize.x / 7.f, m_windowSize.y / 4.f});
	AddBackground("../res/Images/Menu/menu_background1.png", {m_windowSize.x / 1.5f, m_windowSize.y / 2.f});
	AddBackground("../res/Images/Menu/menu_background2.png", {m_windowSize.x / 7.f, m_windowSize.y / 1.7f});
	AddBackground("../res/Images/Menu/menu_background3.png", {m_windowSize.x / 7.f, m_windowSize.y / 7.f});
	m_currentBackground = m_backgrounds.at(myRandom.GetRandomValue(0, m_backgrounds.size() - 1));
	InitBackgroundProgressBar();
}

void CMenuView::InitBackgroundProgressBar()
{
	m_currentBackgroundProgressBar.setSize(sf::Vector2f(0, 5));
	m_currentBackgroundProgressBar.setPosition(0, m_windowSize.y - m_currentBackgroundProgressBar.getGlobalBounds().height);
	m_currentBackgroundProgressBar.setFillColor(sf::Color(230, 230, 230));
}

void CMenuView::SetBackgroundChangingTimeSec(float value)
{
	m_backgroundChangingTimeSec = value;
}

void CMenuView::AddBackground(const std::string & imagePath,const sf::Vector2f & menuPosition)
{
	CMenuBackground * background = new CMenuBackground;
	background->SetSprite(imagePath, m_windowSize);
	background->SetMenuPosition(menuPosition);
	m_backgrounds.push_back(background);
}

void CMenuView::AddMenuItem(MenuItem * menuItem)
{
	m_menu.AddMenuItem(menuItem);
}

void CMenuView::Draw(sf::RenderTarget &target)
{
	if (m_backgroundClock.getElapsedTime().asSeconds() >= m_backgroundChangingTimeSec)
	{
		do
		{
			m_nextBackground = m_backgrounds.at(myRandom.GetRandomValue(0, m_backgrounds.size() - 1));
		}
		while (m_currentBackground == m_nextBackground);
		m_backgroundClock.restart();
		m_animationClock.restart();
		m_menu.Hide();
	}
	else
	{
		float percentage = m_backgroundClock.getElapsedTime().asSeconds() / m_backgroundChangingTimeSec;
		m_currentBackgroundProgressBar.setSize(sf::Vector2f(percentage * m_windowSize.x, m_currentBackgroundProgressBar.getGlobalBounds().height));
	}
	if (m_animationClock.getElapsedTime().asSeconds() >= m_animationTimeSec && m_nextBackground)
	{
		m_currentBackground = m_nextBackground;
		m_menu.Show();
	}
	else if (m_nextBackground)
	{
		AnimateBackgroundChanging();
	}
	if (m_currentBackground)
	{
		m_currentBackground->Draw(target);
		m_menu.SetPosition(m_currentBackground->GetMenuPosition());
	}
	if (m_nextBackground)
	{
		m_nextBackground->Draw(target);
	}
	target.draw(m_currentBackgroundProgressBar);
	m_menu.Draw(target);
}

void CMenuView::Process(sf::RenderWindow & window)
{
	m_menu.Process(window);
}

void CMenuView::AnimateBackgroundChanging()
{
	float percentage = m_animationClock.getElapsedTime().asSeconds() / m_animationTimeSec;
	m_nextBackground->SetTransparent(percentage * 255);
}
