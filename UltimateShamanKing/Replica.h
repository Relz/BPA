// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ULTIMATE_SHAMAN_KING_REPLICA_H
#define ULTIMATE_SHAMAN_KING_REPLICA_H

class CReplica
{
public:
	CReplica(const std::wstring & name, sf::Sprite * avatarSprite, const sf::View & camera, const std::wstring & message);
	void Draw(sf::RenderTarget & target) const;

private:
	sf::Sprite * m_avatarSprite;
	sf::Text m_name;
	sf::Font m_nameFont;
	sf::Text m_message;
	sf::Font m_messageFont;
	sf::RectangleShape m_messageBackground;
};


#endif //ULTIMATE_SHAMAN_KING_REPLICA_H
