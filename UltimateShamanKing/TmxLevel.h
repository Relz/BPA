#ifndef ULTIMATE_SHAMAN_KING_TMXLEVEL_H
#define ULTIMATE_SHAMAN_KING_TMXLEVEL_H

#include "constant.h"
#include "lib/tinyxml2/tinyxml2.h"

struct TmxObject
{
	std::string name;
	std::string type;
	sf::FloatRect rect;
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

	std::vector<TmxObject> GetAllObjectsByName(const std::string & name) const;
	std::vector<TmxObject> GetAllObjectsByType(const std::string & type) const;

	void Draw(sf::RenderTarget & target) const;
	sf::FloatRect GetPlayerRect() const;
	float GetMapLeftBorder() const;
	float GetMapRightBorder() const;

private:
	int m_width = 0;
	int m_height = 0;
	int m_tileWidth = 0;
	int m_tileHeight = 0;
	int m_firstTileID = 0;
	sf::Texture m_tilesetImage;
	std::vector<TmxObject> m_objects;
	std::vector<TmxLayer> m_layers;
	sf::FloatRect m_playerRect;

	int m_firstEnvironmentObjectID = 0;
	std::map<int, EnvironmentObject> m_environmentObjects;

	float m_mapLeftBorder = 0;
	float m_mapRightBorder = 0;
};

#endif //ULTIMATE_SHAMAN_KING_TMXLEVEL_H
