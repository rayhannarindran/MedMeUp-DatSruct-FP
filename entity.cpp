#include <iostream>
#include <SFML/Graphics.hpp>

#include "entity.h"

void Entity::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

sf::Vector2f Entity::getPosition()
{
    return position;
}

sf::Sprite Entity::getSprite()
{
    return sprite;
}

sf::Texture Entity::getTexture()
{
    return texture;
}

sf::RectangleShape Entity::getHitbox()
{
    return hitbox;
}

sf::Vector2f Entity::getHb0()
{
    return hb0;
}

sf::Vector2f Entity::getHb1()
{
    return hb1;
}
