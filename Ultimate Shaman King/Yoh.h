#ifndef ULTIMATE_SHAMAN_KING_YOH_H
#define ULTIMATE_SHAMAN_KING_YOH_H
#include "Drawable.h"


class CYoh : public CDrawable
{
public:
    CYoh(sf::Vector2f startPos);
    ~CYoh() = default;

    void update();

    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;

private:
};


#endif //ULTIMATE_SHAMAN_KING_YOH_H
