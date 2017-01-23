// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_SNOWBALL_H
#define ULTIMATE_SHAMAN_KING_SNOWBALL_H

class CSnowball
{
public:
	void Init(sf::Vector2f startPosition, float directionX, float speed, float maxLivingTimeSec, float strength);
	void SetImage(const std::string & imagePath, float zoom);
	void Draw(sf::RenderTarget & target) const;
	void Process();
	void Hide();

	float GetLivingTimeSec() const;
	float GetMaxLivingTimeSec() const;
	sf::FloatRect GetTextureFloatRect() const;
	float GetStrength() const;
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	float m_directionX = 0;
	float m_speed = 0;
	float m_maxLivingTimeSec = 0;
	float m_strength = 0;
	bool m_hidden = false;

	sf::Clock m_livingClock;
};


#endif //ULTIMATE_SHAMAN_KING_SNOWBALL_H
