// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_MENUVIEW_H
#define ULTIMATE_SHAMAN_KING_MENUVIEW_H

#include "../Random.h"
#include "MenuBackground.h"
#include "Menu.h"

class CMenuView
{
public:
	CMenuView(const sf::Vector2u & windowSize);
	void SetBackgroundChangingTimeSec(float value);
	void AddBackground(const std::string & imagePath, const sf::Vector2f & menuPosition);
	void AddMenuItem(MenuItem * menuItem);
	void Draw(sf::RenderTarget & target);
	void Process(sf::RenderWindow & window);

private:
	void InitBackgroundProgressBar();
	void AnimateBackgroundChanging();
	sf::Vector2u m_windowSize;
	sf::Clock m_backgroundClock;
	float m_backgroundChangingTimeSec = 0;

	sf::Clock m_animationClock;
	float m_animationTimeSec = 1.5;

	std::vector<CMenuBackground*> m_backgrounds;
	CMenuBackground * m_currentBackground = nullptr;
	CMenuBackground * m_nextBackground = nullptr;

	sf::RectangleShape m_currentBackgroundProgressBar;
	CMenu m_menu;

};


#endif //ULTIMATE_SHAMAN_KING_MENUVIEW_H
