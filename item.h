#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "entity.h"

class Item : public Entity
{
private:
    int type;
    bool active;

public:
    Item();
    ~Item();
    void setSprite();
    void setType(int x);
    int getType();
    void setHitbox();
    bool isActive();
    void setActive(int pItem, sf::Vector2f phb0, sf::Vector2f phb1);
};