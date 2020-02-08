// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_MONEYPANEL_H
#define ULTIMATE_SHAMAN_KING_MONEYPANEL_H


class CMoneyPanel
{
public:
	void Init(const std::string & currencyName, float padding);
	void Draw(sf::RenderTarget & target) const;
	void SetPosition(const sf::Vector2f & position);
	void SetMoney(float value);

private:
	std::string m_currencyName;
	float m_padding = 0;
	float m_money = 0;

	sf::Font m_font;
	sf::Text m_text;

	sf::RectangleShape m_background;

};


#endif //ULTIMATE_SHAMAN_KING_MONEYPANEL_H
