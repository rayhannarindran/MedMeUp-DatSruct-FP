#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "entity.h"
#include "player.h"
#include "npc.h"
#include "item.h"
#include "trash.h"
//#include "bullet.h"

class gameManager
{
private:
    //Player
    Player* p;
    bool up, right, down, left, enter;
    
    //Trash
    Trash* t;

    //class Bullet bullet; //temp

    //NPC
    std::vector<NPC*> npc;
    std::vector<NPC*> npcDummy;

    //Item
    std::vector<Item*> it;
    
    //Game
    sf::Clock clock;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;
    sf::Text gameOverScore;
    sf::Music music;

    sf::Font enterFont;
    sf::Text enterText;
    bool resetState;

public:
    gameManager();
    ~gameManager();
    void start();
    void event(const sf::Event&);
    void update();
    void draw(sf::RenderWindow&);
    bool getResetState();
};