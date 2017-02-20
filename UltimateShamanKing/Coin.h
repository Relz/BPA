// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_COIN_H
#define ULTIMATE_SHAMAN_KING_COIN_H


class CCoin
{
public:
	void Init(float value, sf::Vector2f position);
	void Draw(sf::RenderTarget & target) const;
	void SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom);
	void SetSprite(const std::string & spritePath, float zoom);
	void Process();
	sf::FloatRect GetSpriteRect() const;
	float GetValue() const;

private:
	void SetTexture(sf::Texture & texture, const std::string & texturePath);
	void Animate();

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	float m_value = 0;

	size_t m_currentAnimationSprite = 0;
	sf::Clock m_animationClock;

};


#endif //ULTIMATE_SHAMAN_KING_COIN_H
