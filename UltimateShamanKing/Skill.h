// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_SKILL_H
#define ULTIMATE_SHAMAN_KING_SKILL_H

class CSkill
{
public:
	CSkill(const std::string & iconPath, const std::string & name, float size, bool isCanBeUsedOnlyWithSpirit, float spReduce);
	void Draw(sf::RenderTarget & target) const;
	void SetPosition(const sf::Vector2f & position);
	float GetSize() const;
	std::string GetName() const;
	bool IsCanBeUsedOnlyWithSpirit() const;
	void SetMonochrome(bool value);
	float GetSpReduce() const;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Image m_image;

	std::string m_name;
	bool m_isCanBeUsedOnlyWithSpirit = false;

	float m_spReduce = 0;

};


#endif //ULTIMATE_SHAMAN_KING_SKILL_H
