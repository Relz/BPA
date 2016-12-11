#include "stdafx.h"
#include "Level.h"

using namespace tinyxml2;

Object Level::GetObject(std::string name)
{
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
    std::vector<Object> vec;
    for(int i = 0; i < objects.size(); i++)
        if(objects[i].name == name)
            vec.push_back(objects[i]);

    return vec;
}

sf::Vector2i Level::GetTileSize()
{
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window)
{
    for(size_t layer = 0; layer < layers.size(); layer++)
    {
        for (size_t tile = 0; tile < layers[layer].tiles.size(); tile++)
        {
            window.draw(layers[layer].tiles[tile]);
        }
    }
}


bool Level::LoadFromFile(const char *filename)
{
    XMLDocument levelFile;

    if(levelFile.LoadFile(filename) != XML_SUCCESS)
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    XMLElement *map;
    map = levelFile.FirstChildElement("map");

    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    XMLElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    XMLElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    sf::Image img;

    if(!img.loadFromFile(imagepath))
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    img.createMaskFromColor(sf::Color(109, 159, 185));
    tilesetImage.loadFromImage(img);
    tilesetImage.setSmooth(false);

    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;

    std::vector<sf::Rect<int>> subRects;

    for(int y = 0; y < rows; y++)
        for(int x = 0; x < columns; x++)
        {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    XMLElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while(layerElement)
    {
        Layer layer;

        if (layerElement->Attribute("opacity") != NULL)
        {
            float opacity = float(strtod(layerElement->Attribute("opacity"), NULL));
            layer.opacity = 255 * int(opacity);
        }
        else
        {
            layer.opacity = 255;
        }

        XMLElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if(layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        XMLElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while(tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            if (subRectToUse >= 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(float(x * tileWidth), float(y * tileHeight));
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width)
            {
                x = 0;
                y++;
                if(y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    XMLElement *objectGroupElement;

    if (map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while(objectElement)
            {
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setPosition(float(x), float(y));
                int subRectToUse = atoi(objectElement->Attribute("gid")) - firstTileID;

                if (objectElement->Attribute("width") != NULL)
                {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else
                {
                    width = subRects[subRectToUse].width;
                    height = subRects[subRectToUse].height;
                    sprite.setTextureRect(subRects[subRectToUse]);
                }

                sprite.setTextureRect(sf::Rect<int>(subRectToUse * width, 0, width, height));

                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                XMLElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    XMLElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while(prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

#if 0

bodyDef.position.Set(position.x + tileSize.x / 2 * (globalBounds.width / tileSize.x - 1),
                     position.y + 0.5 * (globalBounds.height - tileSize.y));
#endif
// tileSize.x / 2 * (layers[i].tiles[j].getGlobalBounds().width / tileSize.x - 1)
sf::Vector2f GetRectCenter(const sf::FloatRect &rect)
{
    return { rect.left + rect.width * 0.5, rect.top + rect.height * 0.5 };
}

void Level::InitTiles(Level & level, b2World & world)
{
    sf::Vector2i tileSize = level.GetTileSize();
    for(int i = 0; i < layers.size(); i++)
    {
        for(int j = 0; j < layers[i].tiles.size(); j++)
        {
            const sf::Vector2f bodyCenter = GetRectCenter(layers[i].tiles[j].getGlobalBounds()) - sf::Vector2f(tileSize / 2);
            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(bodyCenter.x, bodyCenter.y);
            b2Body *body = world.CreateBody(&bodyDef);
            b2PolygonShape shape;
            shape.SetAsBox(layers[i].tiles[j].getGlobalBounds().width / 2, layers[i].tiles[j].getGlobalBounds().height / 2);
            body->CreateFixture(&shape, 1.0f);
        }
    }
}