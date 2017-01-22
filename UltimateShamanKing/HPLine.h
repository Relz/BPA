#ifndef ULTIMATE_SHAMAN_KING_HPLINE_H
#define ULTIMATE_SHAMAN_KING_HPLINE_H

class CHPLine
{
public:
	CHPLine();
	void SetPosition(const sf::Vector2f & position);
	void SetPosition(float x, float y);
	void Move(float x, float y);
	void SetHP(float value);
	void Draw(sf::RenderTarget & target) const;
private:
	sf::RectangleShape m_outline;
	sf::RectangleShape m_hp;
};


#endif //ULTIMATE_SHAMAN_KING_HPLINE_H
