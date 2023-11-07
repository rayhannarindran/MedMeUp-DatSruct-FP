#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "entity.h"

class Player : public Entity
{
private:
    //Mechanics
    sf::Vector2f vel;
    int direction;
    bool up, left, down, right;
    int item;

    //Health Bar
    int health;
    std::vector<sf::CircleShape> healthBar;
    
    //Game Scoresd
    int score;
    sf::Text scoreText;
    sf::Font scoreFont;

public:
    Player();
    ~Player();
    void setSprite(); //SETTING PLAYER SPRITE
    void setBool(bool UP, bool RIGHT, bool DOWN, bool LEFT);
    void setDirection();
    void Move();
    void setItemI(int type, sf::Vector2f ibp0, sf::Vector2f ibp1, bool tActive);
    void setItemN(int type, sf::Vector2f ibp0, sf::Vector2f ibp1, bool tActive);
    int getItem();
    void setHitbox();
    void setHealth(int anger);
    int getHealth();
    void setHealthBar();
    std::vector<sf::CircleShape> getHealthBar();
    void setTime(float duration);
    sf::Text getScore();
};