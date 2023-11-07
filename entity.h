#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Entity : public sf::Sprite
{
protected:
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape hitbox;
    sf::Vector2f hb0, hb1;
    float scale;

public:
    void setPosition(int x, int y);
    sf::Vector2f getPosition();
    sf::Sprite getSprite();
    sf::Texture getTexture();
    sf::RectangleShape getHitbox();
    sf::Vector2f getHb0();
    sf::Vector2f getHb1();
};