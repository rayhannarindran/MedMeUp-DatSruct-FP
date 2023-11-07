#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "entity.h"
#include "bullet.h"

class NPC : public Entity
{
private:
    //Mechanics
    sf::Clock clock;
    int type;
    bool active;

    //Sprite
    sf::IntRect spriteRect;
    sf::IntRect spriteArr[5];

    sf::IntRect spriteDrip;
    sf::IntRect spriteOld;
    sf::IntRect spriteBandage;
    sf::IntRect spriteHair;
    sf::IntRect spriteBald;

    //Anger
    sf::Uint64 anger;
    float angerThreshold;
    float tempAnger;
    sf::RectangleShape angerBar;
    sf::Uint8 durp1;

    //Text
    sf::Font npcFont;
    sf::Text npcText;

    //Bullets
    std::vector<Bullet> bullets;

public:
    NPC();
    ~NPC();
    void setSprite(); //SETTING NPC SPRITE
    void updateSprite(sf::IntRect newRect);
    void randomSprite();
    sf::IntRect getNPCRect();
    sf::Text getNPCText();

    void setType(int x);
    int getType();

    void setHitbox();
    void setActive(int pItem, sf::Vector2f phb0, sf::Vector2f phb1);
    bool isActive();

    void setAnger();
    sf::Uint64 getAnger();
    void setAngerBar();
    sf::RectangleShape getAngerBar();

   // void setBullet(sf::Time gameDuration); //BULLET -> MORE BULLETS COMING OUT AS THE GAME GOES

};