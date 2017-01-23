// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_MENUBACKGROUND_H
#define ULTIMATE_SHAMAN_KING_MENUBACKGROUND_H


class CMenuBackground
{
public:
	void SetSprite(const std::string & imagePath, const sf::Vector2u & windowSize);
	void SetMenuPosition(const sf::Vector2f & menuPosition);
	void Draw(sf::RenderTarget & target) const;
	sf::Vector2f GetMenuPosition() const;
	void SetTransparent(sf::Uint8 value);

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_menuPosition;
};


#endif //ULTIMATE_SHAMAN_KING_MENUBACKGROUND_H
