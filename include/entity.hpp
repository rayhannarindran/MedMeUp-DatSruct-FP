#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Entity : public sf::Sprite
{
protected:
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
    int x1; int y1; int x2; int y2;
    int scale;

public:
    void setPosition(int x, int y);
    sf::Vector2f getPosition();
    sf::Sprite getSprite();
    sf::Texture getTexture();
};