#ifndef ULTIMATE_SHAMAN_KING_OBJECT_H
#define ULTIMATE_SHAMAN_KING_OBJECT_H

struct Object
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

#endif //ULTIMATE_SHAMAN_KING_OBJECT_H
