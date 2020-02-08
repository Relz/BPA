// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_MENU_H
#define ULTIMATE_SHAMAN_KING_MENU_H

struct MenuItem
{
	friend class CMenu;
public:
	MenuItem(const std::string & textStr, bool & clicked)
		: m_clicked(clicked)
	{
		if (!m_font.loadFromFile("../res/Fonts/arial.ttf"))
		{
			throw std::invalid_argument("Failed to load \"../res/Fonts/arial.ttf\"");
		}
		m_text.setFont(m_font);
		m_text.setString(textStr);
		m_text.setCharacterSize(40);
		m_text.setFillColor(sf::Color::Black);
		m_text.setOutlineThickness(2);
		m_text.setOutlineColor(sf::Color::White);
	}

	void SetPosition(const sf::Vector2f position)
	{
		m_text.setPosition(position);
	}

	void Draw(sf::RenderTarget &target) const
	{
		target.draw(m_text);
	}

	void SetFocus(bool value)
	{
		if (value)
		{
			m_text.setFillColor(sf::Color::Blue);
		}
		else
		{
			m_text.setFillColor(sf::Color::Black);
		}
	}

	void SetClicked(bool value)
	{
		m_clicked = value;
	}

private:
	size_t GetCharacterSize()
	{
		return m_text.getCharacterSize();
	}

	sf::Text m_text;
	bool & m_clicked;
	sf::Font m_font;
};

class CMenu
{
public:
	void AddMenuItem(MenuItem * menuItem);
	void SetPosition(const sf::Vector2f & position);
	void Draw(sf::RenderTarget & target);
	void Hide();
	void Show();
	void Process(sf::RenderWindow & window);
	bool IsVisible() const;
private:
	void UpdateMenuItemsPosition();
	std::vector<MenuItem*> m_menuItems;
	sf::Vector2f m_position;
	bool m_visible = true;
};


#endif //ULTIMATE_SHAMAN_KING_MENU_H
