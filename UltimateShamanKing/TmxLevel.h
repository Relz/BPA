#ifndef ULTIMATE_SHAMAN_KING_TMXLEVEL_H
#define ULTIMATE_SHAMAN_KING_TMXLEVEL_H

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

struct TmxObject
{
	std::string name;
	std::string type;
	sf::IntRect rect;
	bool topCollision;
	bool rightCollision;
	bool bottomCollision;
	bool leftCollision;
	std::map<std::string, std::string> properties;

	sf::Sprite sprite;
};

struct TmxLayer
{
	float opacity = 0;
	std::vector<sf::Sprite> tiles;
};

struct EnvironmentObject
{
	std::string imagePath;
	sf::Texture imageTexture;
	float originalWidth = 0;
	float originalHeight = 0;
	sf::IntRect rect;
};

class TmxLevel
{
public:
	bool LoadFromFile(const std::string & filepath);

	TmxObject GetFirstObject(const std::string & name) const;
	std::vector<TmxObject> GetAllObjectsByName(const std::string & name) const;
	std::vector<TmxObject> GetAllObjectsByType(const std::string & type) const;
	sf::Vector2i GetTileSize() const;

	void Draw(sf::RenderTarget & target) const;
	sf::IntRect GetPlayerRect() const;

private:
	int m_width = 0;
	int m_height = 0;
	int m_tileWidth = 0;
	int m_tileHeight = 0;
	int m_firstTileID = 0;
	sf::Texture m_tilesetImage;
	std::vector<TmxObject> m_objects;
	std::vector<TmxLayer> m_layers;
	sf::IntRect m_playerRect;

	int m_firstEnvironmentObjectID = 0;
	std::map<int, EnvironmentObject> m_environmentObjects;
};

#endif //ULTIMATE_SHAMAN_KING_TMXLEVEL_H
