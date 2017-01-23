#ifndef ULTIMATE_SHAMAN_KING_GAMEOVER_H
#define ULTIMATE_SHAMAN_KING_GAMEOVER_H

class CGameOver
{
public:
	CGameOver();
	void Draw(sf::RenderTarget & target);
	void SetWindowCenter(const sf::Vector2f & windowCenter);
	void SetWindowSize(const sf::Vector2u & windowSize);
	void SetBackgroundScale(float x, float y);
	float GetBackgroundWidth() const;
private:
	void InitBackground(const std::string & imagePath);
	void InitText(const std::string & textMessage, const std::string & fontPath);
	void InitSubText(const std::string & textMessage, const std::string & fontPath);
	void InitTextFont(const std::string & fontPath);
	void InitSubTextFont(const std::string & fontPath);

	sf::Text m_text;
	sf::Text m_subText;
	sf::Sprite m_background;

	sf::Font m_textFont;
	sf::Font m_subTextFont;
	sf::Texture m_backgroundTexture;

	sf::Vector2f m_windowCenter;
	sf::Vector2u m_windowSize;
};


#endif //ULTIMATE_SHAMAN_KING_GAMEOVER_H
