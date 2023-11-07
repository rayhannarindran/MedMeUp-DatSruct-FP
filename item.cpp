#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "item.h"
#include "player.h"

Item::Item()
{
    scale = 2.5;
    position = sf::Vector2f((std::rand() % (1350 - 250 + 1) + 250), (std::rand() % (800 - 380 + 1)) + 380);
    type = 1; //1 Bone Med, 2 Heart Med, 3 Brain Med 
    active = true;
    sprite.setOrigin(13, 15);
}

Item::~Item()   
{
    
}

void Item::setSprite()
{
    switch (type)
    {
    case 1:
        texture.loadFromFile("sprites/Items/BoneMed.png");
        break;
    case 2:
        texture.loadFromFile("sprites/Items/HeartMed.png");
        break;
    case 3:
        texture.loadFromFile("sprites/Items/BrainMed.png");
        break;
    }
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
}

void Item::setType(int x)
{
    type = x;
}

int Item::getType()
{
    return type;
}

void Item::setHitbox()
{
    hitbox.setSize(sf::Vector2f(32, 45));
    hitbox.setPosition(position.x - 11, position.y - 20);
    hb0 = hitbox.getTransform().transformPoint(hitbox.getPoint(0));
    hb1 = hitbox.getTransform().transformPoint(hitbox.getPoint(2));
}

bool Item::isActive()
{
    return active;
}

void Item::setActive(int pItem, sf::Vector2f phb0, sf::Vector2f phb1)
 {
    if ((pItem == 0) && (hb0.x < phb1.x && hb0.y < phb1.y) && (hb1.x > phb0.x && hb1.y > phb0.y))
    {
        active = false;
    }
 }