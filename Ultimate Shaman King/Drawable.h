#ifndef ULTIMATE_SHAMAN_KING_CDRAWABLE_H
#define ULTIMATE_SHAMAN_KING_CDRAWABLE_H


class CDrawable
{
public:
    CDrawable(sf::Shape *model);
    ~CDrawable() = default;

    sf::Shape const* getModel() const;
protected:
    sf::Shape *m_model = nullptr;
};

#endif //ULTIMATE_SHAMAN_KING_CDRAWABLE_H
