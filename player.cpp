#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "Player.h"

Player::Player()
{
    score = 0;
    health = 3;
    scale = 3;
    position = sf::Vector2f(100, 800);
    vel = sf::Vector2f(0, 0);
    direction = 0; //0 Up, 1 Left, 2 Down, 3 Right
    item = 0; //0 Empty; 1 Bone Med; 2 Heart Med; 3 Brain Med
    sprite.setOrigin(14, 14);

    for (int i = 0; i < 3; i++)
    {
        sf::CircleShape circle;
        healthBar.push_back(circle);
        healthBar[i].setRadius(5);
        healthBar[i].setFillColor(sf::Color::Red);
    }

    //Scoring
    scoreFont.loadFromFile("sprites/ARLRDBD.TTF");
    scoreText.setString("Score " + std::to_string(score));
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineThickness(3);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setPosition(20, 20);
}

Player::~Player()
{

}

void Player::setSprite()
{
    switch (item)
    {
    case 0:
        switch (direction)
        {
        case 0:
            texture.loadFromFile("sprites/Player/UP1.png");
            break;
        case 1:
            texture.loadFromFile("sprites/Player/LEFT1.png");
            break;
        case 2:
            texture.loadFromFile("sprites/Player/DOWN1.png");
            break;
        case 3:
            texture.loadFromFile("sprites/Player/RIGHT1.png");
            break;
        }
        break;

    case 1:
        switch (direction)
        {
        case 0:
            texture.loadFromFile("sprites/Player/BONE/BUP1.png");
            break;
        case 1:
            texture.loadFromFile("sprites/Player/BONE/BLEFT1.png");
            break;
        case 2:
            texture.loadFromFile("sprites/Player/BONE/BDOWN1.png");
            break;
        case 3:
            texture.loadFromFile("sprites/Player/BONE/BRIGHT1.png");
            break;
        }
        break;
    case 2:
        switch (direction)
        {
        case 0:
            texture.loadFromFile("sprites/Player/HEART/HUP1.png");
            break;
        case 1:
            texture.loadFromFile("sprites/Player/HEART/HLEFT1.png");
            break;
        case 2:
            texture.loadFromFile("sprites/Player/HEART/HDOWN1.png");
            break;
        case 3:
            texture.loadFromFile("sprites/Player/HEART/HRIGHT1.png");
            break;
        }
        break;
    case 3:
        switch (direction)
        {
        case 0:
            texture.loadFromFile("sprites/Player/BRAIN/RUP1.png");
            break;
        case 1:
            texture.loadFromFile("sprites/Player/BRAIN/RLEFT1.png");
            break;
        case 2:
            texture.loadFromFile("sprites/Player/BRAIN/RDOWN1.png");
            break;
        case 3:
            texture.loadFromFile("sprites/Player/BRAIN/RRIGHT1.png");
            break;
        }
        break;
    }

    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
}

void Player::setBool(bool UP, bool RIGHT, bool DOWN, bool LEFT)
{
    up = UP;
    left = LEFT;
    down = DOWN;
    right = RIGHT;
}

void Player::setDirection()
{
    if (up) { direction = 0; }
    if (left) { direction = 1; }
    if (down) { direction = 2; }
    if (right) { direction = 3; }
}

void Player::Move()
{
    float vel_num = 8;
    float normalized = vel_num / std::sqrt(2);

    if (up) { vel = sf::Vector2f(0, -vel_num); }
    if (down) { vel = sf::Vector2f(0, vel_num); }
    if (right) { vel = sf::Vector2f(vel_num, 0); }
    if (left) { vel = sf::Vector2f(-vel_num, 0); }
    if (up && right) { vel = sf::Vector2f(normalized, -normalized); }
    if (up && left) { vel = sf::Vector2f(-normalized, -normalized); }
    if (down && right) { vel = sf::Vector2f(normalized, normalized); }
    if (down && left) { vel = sf::Vector2f(-normalized, normalized); }

    vel += sf::Vector2f(vel.x * -1 / 5, vel.y * -1 / 5);
    position += vel;
}

void Player::setHitbox()
{
    hitbox.setSize(sf::Vector2f(33, 100));
    hitbox.setPosition(position.x - 10, position.y - 40);
    hb0 = hitbox.getTransform().transformPoint(hitbox.getPoint(0));
    hb1 = hitbox.getTransform().transformPoint(hitbox.getPoint(2));
};

void Player::setItemI(int type, sf::Vector2f ihb0, sf::Vector2f ihb1, bool tActive)
{
    if ((item == 0) && (hb0.x < ihb1.x && hb0.y < ihb1.y) && (hb1.x > ihb0.x && hb1.y > ihb0.y))
    {
        switch (type)
        {
        case 0:
            item = 0;
            break;
        case 1:
            item = 1;
            break;

        case 2:
            item = 2;
            break;

        case 3:
            item = 3;
            break;
        };
    }
    else if ((item != 0) && (tActive))
    {
        item = 0;
    }
};

void Player::setItemN(int type, sf::Vector2f ihb0, sf::Vector2f ihb1, bool tActive)
{
    if ((item != 0) && (item == type) && (hb0.x < ihb1.x && hb0.y < ihb1.y) && (hb1.x > ihb0.x && hb1.y > ihb0.y))
    {
        score += 50;
        scoreText.setString("Score " + std::to_string(score));

        item = 0;
    } 
    if ((item != 0) && (item != type) && (hb0.x < ihb1.x && hb0.y < ihb1.y) && (hb1.x > ihb0.x && hb1.y > ihb0.y))
    {
        score -= 10;
        scoreText.setString("Score " + std::to_string(score));

        item = 0;
    }
    else if ((item != 0) && (tActive))
    {
        item = 0;
    }
};

int Player::getItem()
{
    return item;
}

void Player::setHealth(int anger)
{
    if (anger >= 15)
    {
        health--;
    }
}

int Player::getHealth()
{
    return health;
}

void Player::setHealthBar()
{
    switch (health)
    {
    case 1:
        healthBar[0].setPosition(position.x - 11, position.y - 55);
        healthBar[1].setPosition(-100, -100);
        healthBar[2].setPosition(-100, -100);
        break;

    case 2:
        healthBar[0].setPosition(position.x - 11, position.y - 55);
        healthBar[1].setPosition(position.x + 2, position.y - 55);
        healthBar[2].setPosition(-100, -100);
        break;

    case 3:
        healthBar[0].setPosition(position.x - 11, position.y - 55);
        healthBar[1].setPosition(position.x + 2, position.y - 55);
        healthBar[2].setPosition(position.x + 15, position.y - 55);
        break;

    default:
        healthBar[0].setPosition(-100, -100);
        healthBar[1].setPosition(-100, -100);
        healthBar[2].setPosition(-100, -100);
        break;
    }
}

std::vector<sf::CircleShape> Player::getHealthBar()
{
    return healthBar;
}

sf::Text Player::getScore()
{
    return scoreText;
}

