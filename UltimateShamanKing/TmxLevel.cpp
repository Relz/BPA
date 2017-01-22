// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "TmxLevel.h"

using namespace tinyxml2;

// On Windows, backslash '\\' is directory separator in paths
// On UNIX paths separated with slash '/'.
#if defined(_WIN32)
const char DIR_SEPARATOR = '\\';
#else
const char DIR_SEPARATOR = '/';
#endif

// Returns parent directory of given path;
std::string GetParentDirectory(const std::string &filepath)
{
	const size_t slashPos = filepath.find_last_of('/');
	std::string parentDir;
	if (slashPos != std::string::npos)
	{
		parentDir = filepath.substr(0, slashPos);
	}
	return parentDir;
}

// Joins two path fragments, e.g. directory path and filename
std::string JoinPaths(const std::string &path, const std::string &subpath)
{
	if (path.empty())
	{
		return subpath;
	}
	if (subpath.empty())
	{
		return path;
	}

	return path + DIR_SEPARATOR + subpath;
}

static void PrintWarning(const std::string & msg)
{
	std::cout << "Warning: " << msg << "\n";
}

static void PrintError(const std::string & msg)
{
	std::cout << "Error: " << msg << "\n";
}

// Parses hex-encoded RGB like "6d9fb9"
sf::Color ParseColor(const std::string &hexRGB)
{
	char *pEnd = nullptr;
	const long hexValue = strtol(hexRGB.c_str(), &pEnd, 16);
	if (*pEnd != '\0')
	{
		throw std::runtime_error(hexRGB + " is not valid hex-encoded RGB color");
	}

	const uint8_t red = uint8_t((hexValue >> 16) % 256);
	const uint8_t green = uint8_t((hexValue >> 8) % 256);
	const uint8_t blue = uint8_t(hexValue % 256);

	return sf::Color(red, green, blue);
}

bool TmxLevel::LoadFromFile(const std::string &filepath)
{
	XMLDocument levelFile;

	if(levelFile.LoadFile(filepath.c_str()) != XML_SUCCESS)
	{
		throw std::runtime_error("Loading level \"" + filepath + "\" failed.");
	}

	XMLElement *map = levelFile.FirstChildElement("map");
	if (map == 0)
	{
		throw std::runtime_error("<map> element not found");
	}

	if (map->QueryIntAttribute("width", &m_width) != XML_SUCCESS)
	{
		PrintError("map width not specified");
		return false;
	}
	if (map->QueryIntAttribute("height", &m_height) != XML_SUCCESS)
	{
		PrintError("map height not specified");
		return false;
	}
	if (map->QueryIntAttribute("tilewidth", &m_tileWidth) != XML_SUCCESS)
	{
		PrintError("map tilewidth not specified");
		return false;
	}
	if (map->QueryIntAttribute("tileheight", &m_tileHeight) != XML_SUCCESS)
	{
		PrintError("map tileheight not specified");
		return false;
	}

	XMLElement *tilesetElement = map->FirstChildElement("tileset");

	while (tilesetElement)
	{
		if (tilesetElement->Attribute("name") == TMX_TILES)
		{
			m_firstTileID = 0;
			if (tilesetElement->QueryIntAttribute("firstgid", &m_firstTileID) != XML_SUCCESS)
			{
				PrintError("tileset firstgid not specified");
				return false;
			}

			XMLElement *image = tilesetElement->FirstChildElement("image");
			const std::string imageFilename = image->Attribute("source");
			const std::string imagePath = JoinPaths(GetParentDirectory(filepath), imageFilename);
			const sf::Color matteColor = sf::Color(255, 255, 255);

			sf::Image img;
			if (!img.loadFromFile(imagePath))
			{
				PrintError("Failed to load tile sheet");
				return false;
			}

			img.createMaskFromColor(matteColor);
			m_tilesetImage.loadFromImage(img);
			m_tilesetImage.setSmooth(false);

			tilesetElement = tilesetElement->NextSiblingElement("tileset");
			continue;
		}
		if (tilesetElement->Attribute("name") == TMX_ENVIRONMENT)
		{
			m_firstEnvironmentObjectID = 0;
			if (tilesetElement->QueryIntAttribute("firstgid", &m_firstEnvironmentObjectID) != XML_SUCCESS)
			{
				PrintError("tileset firstgid not specified");
				return false;
			}
			XMLElement *tileElement = tilesetElement->FirstChildElement("tile");
			if (tileElement == nullptr)
			{
				PrintError("Bad map. No tile information found");
				return false;
			}

			while (tileElement)
			{
				EnvironmentObject environmentObject;
				int environmentObjectID = 0;
				if (tileElement->QueryIntAttribute("id", &environmentObjectID) != XML_SUCCESS)
				{
					PrintError("environment object id not specified");
					return false;
				}

				XMLElement *imageElement = tileElement->FirstChildElement("image");

				if (imageElement->QueryFloatAttribute("width", &environmentObject.originalWidth) != XML_SUCCESS)
				{
					PrintError("environment object width not specified");
					return false;
				}

				if (imageElement->QueryFloatAttribute("height", &environmentObject.originalHeight) != XML_SUCCESS)
				{
					PrintError("environment object height not specified");
					return false;
				}

				environmentObject.imagePath = imageElement->Attribute("source");
				if (environmentObject.imagePath.empty())
				{
					PrintError("environment object source not specified");
					return false;
				}

				std::string imagePath = JoinPaths(GetParentDirectory(filepath), environmentObject.imagePath);
				if (!environmentObject.imageTexture.loadFromFile(imagePath))
				{
					PrintError("Failed to load environment object image " + imagePath);
					return false;
				}
				environmentObject.imageTexture.setSmooth(false);

				m_environmentObjects[environmentObjectID] = environmentObject;
				tileElement = tileElement->NextSiblingElement("tile");
			}
			tilesetElement = tilesetElement->NextSiblingElement("tileset");
			continue;
		}
	}

	const int columns = m_tilesetImage.getSize().x / m_tileWidth;
	const int rows = m_tilesetImage.getSize().y / m_tileHeight;

	std::vector<sf::IntRect> subRects;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			sf::IntRect rect;
			rect.top = y * m_tileHeight;
			rect.height = m_tileHeight;
			rect.left = x * m_tileWidth;
			rect.width = m_tileWidth;
			subRects.push_back(rect);
		}
	}

	XMLElement *layerElement = map->FirstChildElement("layer");
	while (layerElement)
	{
		TmxLayer layer;
		if (layerElement->Attribute("opacity") != nullptr)
		{
			float opacity = 0;
			if (layerElement->QueryFloatAttribute("opacity", &opacity) != XML_SUCCESS)
			{
				PrintWarning("layer opacity not specified, default is " + std::to_string(opacity));
			}
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		XMLElement *layerDataElement = layerElement->FirstChildElement("data");
		if (layerDataElement == nullptr)
		{
			PrintError("Bad map. No layer information found");
			return false;
		}

		XMLElement *tileElement = layerDataElement->FirstChildElement("tile");
		if (tileElement == nullptr)
		{
			PrintError("Bad map. No tile information found");
			return false;
		}

		int x = 0;
		int y = 0;
		while (tileElement)
		{
			int tileGID = 0;
			if (tileElement->QueryIntAttribute("gid", &tileGID) != XML_SUCCESS)
			{
				PrintError("tile gid not specified");
				return false;
			}
			const int subRectToUse = tileGID - m_firstTileID;

			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(m_tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * m_tileWidth, y * m_tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(layer.opacity)));

				layer.tiles.push_back(sprite);
			}

			tileElement = tileElement->NextSiblingElement("tile");

			x++;
			if (x >= m_width)
			{
				x = 0;
				y++;
				if (y >= m_height)
				{
					y = 0;
				}
			}
		}

		m_layers.push_back(layer);
		layerElement = layerElement->NextSiblingElement("layer");
	}

	XMLElement *objectGroupElement = map->FirstChildElement("objectgroup");
	while (objectGroupElement)
	{
		XMLElement *objectElement = objectGroupElement->FirstChildElement("object");

		while (objectElement)
		{
			bool visible = true;
			if (objectElement->QueryBoolAttribute("visible", &visible) != XML_SUCCESS)
			{
				visible = true;
			}
			if (!visible)
			{
				objectElement = objectElement->NextSiblingElement("object");
				continue;
			}
			std::string objectType;
			if (objectElement->Attribute("type") != nullptr)
			{
				objectType = objectElement->Attribute("type");
			}
			std::string objectName;
			if (objectElement->Attribute("name") != nullptr)
			{
				objectName = objectElement->Attribute("name");
			}
			int x = 0;
			if (objectElement->QueryIntAttribute("x", &x) != XML_SUCCESS)
			{
				PrintWarning(objectName + " x not specified, default is " + std::to_string(x));
			}
			int y = 0;
			if (objectElement->QueryIntAttribute("y", &y) != XML_SUCCESS)
			{
				PrintWarning(objectName + " y not specified, default is " + std::to_string(y));
			}
			int width = 0;
			int height = 0;

			bool topCollision = false;
			bool rightCollision = false;
			bool bottomCollision = false;
			bool leftCollision = false;

			sf::Sprite sprite;

			if (objectGroupElement->Attribute("name") == TMX_ENVIRONMENT)
			{
				if (objectElement->QueryIntAttribute("width", &width) != XML_SUCCESS)
				{
					PrintWarning(objectName + " width not specified, default is " + std::to_string(width));
				}
				if (objectElement->QueryIntAttribute("height", &height) != XML_SUCCESS)
				{
					PrintWarning(objectName + " height not specified, default is " + std::to_string(height));
				}
				unsigned int gid = 0;
				if (objectElement->QueryUnsignedAttribute("gid", &gid) != XML_SUCCESS)
				{
					PrintError(objectName + " gid not specified");
					return false;
				}
				int environmentObjectID = gid - m_firstEnvironmentObjectID;
				float originalWidth = m_environmentObjects[environmentObjectID].originalWidth;
				float originalHeight = m_environmentObjects[environmentObjectID].originalHeight;
				m_environmentObjects[environmentObjectID].rect = {0, 0, static_cast<int>(originalWidth), static_cast<int>(originalHeight)};

				sprite.setTexture(m_environmentObjects[environmentObjectID].imageTexture);
				sprite.setTextureRect(m_environmentObjects[environmentObjectID].rect);
				sprite.setPosition(x, y - height);
				sprite.setScale(width / originalWidth, height / originalHeight);
			}
			else if (objectType == TMX_COLLISION_BLOCK)
			{
				sprite.setTexture(m_tilesetImage);
				sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
				sprite.setPosition(x, y);
				if (objectElement->QueryIntAttribute("width", &width) != XML_SUCCESS)
				{
					PrintWarning(objectName + " width not specified, default is " + std::to_string(width));
				}
				if (objectElement->QueryIntAttribute("height", &height) != XML_SUCCESS)
				{
					PrintWarning(objectName + " height not specified, default is " + std::to_string(height));
				}
				XMLElement *properties = objectElement->FirstChildElement("properties");
				if (properties)
				{
					XMLElement *property = properties->FirstChildElement("property");
					while (property)
					{
						std::string propertyName = property->Attribute("name");
						std::string propertyValue = property->Attribute("value");
						if (propertyName == "topCollision")
						{
							topCollision = (propertyValue == "true");
						}
						else if (propertyName == "rightCollision")
						{
							rightCollision = (propertyValue == "true");
						}
						else if (propertyName == "bottomCollision")
						{
							bottomCollision = (propertyValue == "true");
						}
						else if (propertyName == "leftCollision")
						{
							leftCollision = (propertyValue == "true");
						}
						property = property->NextSiblingElement("property");
					}
				}
			}
			else
			{
				sprite.setTexture(m_tilesetImage);
				sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
				sprite.setPosition(x, y);
				int index = 0;
				if (objectElement->QueryIntAttribute("gid", &index) != XML_SUCCESS)
				{
					PrintWarning(objectName + " gid not specified");
					if (objectElement->QueryIntAttribute("width", &width) != XML_SUCCESS)
					{
						PrintWarning(objectName + " width not specified, default is " + std::to_string(width));
					}
					if (objectElement->QueryIntAttribute("height", &height) != XML_SUCCESS)
					{
						PrintWarning(objectName + " height not specified, default is " + std::to_string(height));
					}
				}
				else
				{
					index -= m_firstTileID;
					width = subRects[index].width;
					height = subRects[index].height;
					sprite.setTextureRect(subRects[index]);
				}
				sprite.setOrigin(0, height);
			}

			TmxObject object;
			object.name = objectName;
			object.type = objectType;
			object.sprite = sprite;
			object.topCollision = topCollision;
			object.rightCollision = rightCollision;
			object.bottomCollision = bottomCollision;
			object.leftCollision = leftCollision;

			sf::FloatRect objectRect;
			objectRect.top = (objectName == TMX_PLAYER || objectType == TMX_ENEMY) ? y - height : y;
			objectRect.left = x;
			objectRect.height = height;
			objectRect.width = width;
			object.rect = objectRect;

			XMLElement *properties = objectElement->FirstChildElement("properties");
			if (properties != nullptr)
			{
				XMLElement *property = properties->FirstChildElement("property");
				while (property != nullptr)
				{
					std::string propertyName = property->Attribute("name");
					std::string propertyValue = property->Attribute("value");

					object.properties[propertyName] = propertyValue;

					property = property->NextSiblingElement("property");
				}
			}
			if (objectName == TMX_PLAYER)
			{
				m_playerRect = object.rect;
			}
			else
			{
				m_objects.push_back(object);
			}
			objectElement = objectElement->NextSiblingElement("object");
		}
		objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
	}
	if (m_objects.empty())
	{
		PrintError("No object layers found");
		return false;
	}
	return true;
}

std::vector<TmxObject> TmxLevel::GetAllObjectsByName(const std::string & name) const
{
	std::vector<TmxObject> vec;
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i].name == name)
		{
			vec.push_back(m_objects[i]);
		}
	}
	return vec;
}

std::vector<TmxObject> TmxLevel::GetAllObjectsByType(const std::string & type) const
{
	std::vector<TmxObject> vec;
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i].type == type)
		{
			vec.push_back(m_objects[i]);
		}
	}
	return vec;
}

void TmxLevel::Draw(sf::RenderTarget & target)const
{
	const sf::FloatRect viewportRect = target.getView().getViewport();

	for (const auto &layer : m_layers)
	{
		for (const auto &tile : layer.tiles)
		{
			if (viewportRect.intersects(tile.getLocalBounds()))
			{
				target.draw(tile);
			}
		}
	}
}

sf::FloatRect TmxLevel::GetPlayerRect() const
{
	return m_playerRect;
}
