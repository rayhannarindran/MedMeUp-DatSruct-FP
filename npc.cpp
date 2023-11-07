#include <iostream>
#include <SFML/Graphics.hpp>

#include "npc.h"
#include "bullet.h"

NPC::NPC()
{
    clock.restart();
    scale = 1.75;
    position = sf::Vector2f(700, 700);
    type = 1;
    active = true;
    sprite.setOrigin(12, 12);
    texture.loadFromFile("sprites/npc.png");

    //Rects
    spriteDrip = sf::IntRect(192, 192, 48, 48);
    spriteOld = sf::IntRect(48, 192, 48, 48);
    spriteBandage = sf::IntRect(336, 0, 48, 48);
    spriteHair = sf::IntRect(48, 0, 48, 48);
    spriteBald = sf::IntRect(480, 0, 48, 48);

    spriteArr[0] = spriteDrip;
    spriteArr[1] = spriteOld;
    spriteArr[2] = spriteBandage;
    spriteArr[3] = spriteHair;
    spriteArr[4] = spriteBald;

    spriteRect = spriteArr[std::rand() % 5];

    //Anger
    durp1 = 0;
    angerBar.setSize(sf::Vector2f(50, 15));
    angerBar.setOrigin(sf::Vector2f(6, 6));
    angerBar.setFillColor(sf::Color::Red);
    angerThreshold = 15;

    //Text
    npcFont.loadFromFile("sprites/ARLRDBD.TTF");
    npcText.setFont(npcFont);
    npcText.setCharacterSize(20);
    npcText.setFillColor(sf::Color::White);
    npcText.setOutlineThickness(3);
    npcText.setOutlineColor(sf::Color::Black);
}

NPC::~NPC()
{

}

void NPC::setSprite()
{
    switch (type)
    {
    case 1:
        //spriteRect = spriteArr[std::rand() % 4];
        npcText.setString("  Bone\nPatient");
        npcText.setPosition(position.x - 22, position.y + 90);
        break;

    case 2:
        //spriteRect = spriteOld;
        npcText.setString(" Heart\nPatient");
        npcText.setPosition(position.x - 15, position.y + 90);
        break;

    case 3:
        //spriteRect = spriteHair;
        npcText.setString("  Brain\nPatient");
        npcText.setPosition(position.x - 17, position.y + 90);
        break;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(spriteRect);
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
}

void NPC::updateSprite(sf::IntRect newRect)
{
    spriteRect = newRect;
}

void NPC::randomSprite()
{
    spriteRect = spriteArr[rand() % 5];
}

sf::IntRect NPC::getNPCRect()
{
    return spriteRect;
}

sf::Text NPC::getNPCText()
{
    return npcText;
}

void NPC::setType(int x)
{
    type = x;
}

int NPC::getType()
{
    return type;
}

void NPC::setHitbox()
{
    hitbox.setSize(sf::Vector2f(60, 84));
    hitbox.setPosition(position.x - 11, position.y - 20);
    hb0 = hitbox.getTransform().transformPoint(hitbox.getPoint(0));
    hb1 = hitbox.getTransform().transformPoint(hitbox.getPoint(2));
}

void NPC::setActive(int pItem, sf::Vector2f phb0, sf::Vector2f phb1)
{
    if ((hb0.x < phb1.x && hb0.y < phb1.y) && (hb1.x > phb0.x && hb1.y > phb0.y))
    {
        if (pItem != 0 && pItem != type && anger != angerThreshold)
        {
            if (anger > angerThreshold - 2)
            {
                anger += 1;
            }
            else
            {
                anger += 2;
            }
        }
        else if (pItem == type)
        {
            active = false;
        }
    }
}

bool NPC::isActive()
{
    return active;
}

void NPC::setAnger()
{
    if (anger < angerThreshold)
    {
        sf::Uint64 dur = clock.getElapsedTime().asSeconds();

        if (durp1 < dur)
        {
            durp1++;
            anger += 1;
        }
   
    }
    else if (anger >= angerThreshold)
    {
        active = false;
    }
}

sf::Uint64 NPC::getAnger()
{
    return anger;
}

void NPC::setAngerBar()
{
    angerBar.setPosition(sf::Vector2f(position.x, position.y - 30));
    tempAnger = anger;
    angerBar.setSize(sf::Vector2f(50 * (angerThreshold - tempAnger) / angerThreshold, 15));
}

sf::RectangleShape NPC::getAngerBar()
{
    return angerBar;
}

/*
void NPC::setBullet(sf::Time gameDuration)
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if ((bullets[i].getPosition().x < 1700 && bullets[i].getPosition().x > -100) || (bullets[i].getPosition().y < 1000))
        {

        }
    }
}
*/