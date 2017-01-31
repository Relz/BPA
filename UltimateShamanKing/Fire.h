// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_FIRE_H
#define ULTIMATE_SHAMAN_KING_FIRE_H

enum FireState
{
	SLEEP, PROCESSING, DISSAPPEARED
};

class CFire
{
public:
	void SetSprite(const std::string & spritePath, const sf::IntRect & playerSpriteRect, float zoom);
	void SetPosition(const sf::Vector2f & position);
	void Show(bool doesInvokeDialogAfterProccessing);
	void Process(FireState & fireState);
	bool DoesInvokeDialogAfterProccessing() const;
	void Draw(sf::RenderTarget & target) const;
private:
	void UpdateSprite();
	bool IsVisible() const;

	sf::Sprite m_sprite;
	sf::Texture m_texture;

	bool m_visible = false;

	sf::Clock m_animationClock;
	size_t m_currentSprite = 0;

	sf::Clock m_livingTimeClock;
	float m_maxLivingTimeSec = 1;

	bool m_doesInvokeDialogAfterProccessing = false;

};


#endif //ULTIMATE_SHAMAN_KING_FIRE_H
