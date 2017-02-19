// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_SHIELD_H
#define ULTIMATE_SHAMAN_KING_SHIELD_H


class CShield
{
public:
	void Draw(sf::RenderTarget & target, float lastDirectionX);
	void SetSprite(const std::string & spritePath, float zoom);
	void SetPosition(const sf::Vector2f & position);

private:
	void SetTexture(sf::Texture & texture, const std::string & texturePath);

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	int m_startWidth = 0;
};


#endif //ULTIMATE_SHAMAN_KING_SHIELD_H
