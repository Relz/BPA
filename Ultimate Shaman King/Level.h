#ifndef ULTIMATE_SHAMAN_KING_LEVEL_H
#define ULTIMATE_SHAMAN_KING_LEVEL_H

#include "Layer.h"
#include "Object.h"

class Level
{
public:
    bool LoadFromFile(const char *filename);
    Object GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
    void InitTiles(Level & level, b2World & world);
    void Draw(sf::RenderWindow &window);
    sf::Vector2i GetTileSize();

private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};

#endif //ULTIMATE_SHAMAN_KING_LEVEL_H
