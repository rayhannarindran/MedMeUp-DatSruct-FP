#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "game.h"

//#include "bullet.h" //temp

using namespace std;

gameManager::gameManager()
{
    resetState = false;
    up = false; right = false; down = false; left = false;
    bgTexture.loadFromFile("sprites/test.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(1, 1);
    gameOverTexture.loadFromFile("sprites/GameOver.jpg");
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setScale(1, 1);
    music.openFromFile("gameMusic.ogg");

    enterFont.loadFromFile("sprites/ARLRDBD.TTF");
    enterText.setString("Press Enter to Play Again!");
    enterText.setFont(enterFont);
    enterText.setCharacterSize(60);
    enterText.setFillColor(sf::Color::White);
    enterText.setOutlineThickness(3);
    enterText.setOutlineColor(sf::Color::Black);
    enterText.setPosition(400, 600);
}

gameManager::~gameManager()
{

}

void gameManager::start()
{
    music.play();
    std::srand(std::time(NULL));

    //Player Start
    p = new Player();

    //Trash Start
    t = new Trash();
 
    //NPC Start
    for (int i = 0; i < 3; i++)
    {
        npc.push_back(new NPC());
        npcDummy.push_back(new NPC());

        npc[i]->setType(i + 1);
        npcDummy[i]->setType(i + 1);

        npc[i]->setPosition((400 * (i + 1)), 150);
        npcDummy[i]->setPosition((400 * (i + 1)), 30);
    }

    //Items Start
    for (int i = 0; i < 3; i++)
    {
        it.push_back(new Item());
        it[i]->setType(i+1);
    }
}

void gameManager::event(const sf::Event& ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        switch (ev.key.code)
        {
        case sf::Keyboard::W:
            up = true;
            break;

        case sf::Keyboard::A:
            left = true;
            break;

        case sf::Keyboard::S:
            down = true;
            break;

        case sf::Keyboard::D:
            right = true;
            break;

        case sf::Keyboard::Enter:
            enter = true;
            break;
        };
        break;

    case sf::Event::KeyReleased:
        switch (ev.key.code)
        {
        case sf::Keyboard::W:
            up = false;
            break;

        case sf::Keyboard::A:
            left = false;
            break;

        case sf::Keyboard::S:
            down = false;
            break;

        case sf::Keyboard::D:
            right = false;
            break;

        case sf::Keyboard::Enter:
            enter = false;
            break;
        };
        break;
    };
}

void gameManager::update()
{
    //Player
    p->setBool(up, right, down, left);
    p->setHitbox();
    p->setSprite();
    p->setDirection();
    p->Move();
    p->setHealthBar();

    //NPC
    if (npc.size() == 2)
    {
        int r_type = 6 - (npc[0]->getType()) - (npc[1]->getType());

        npc.push_back(new NPC());
        npc[2]->setType(r_type);
        npc[2]->updateSprite(npcDummy[r_type - 1]->getNPCRect());
        npcDummy[r_type - 1]->randomSprite();
        
        switch (r_type)
        {
        case 1:
            npc[2]->setPosition(400, 150);
            break;
        case 2:
            npc[2]->setPosition(800, 150);
            break;
        case 3:
            npc[2]->setPosition(1200, 150);
            break;
        }
    }

    for (unsigned int i = 0; i < npc.size(); i++)
    {
        //Player Health Based on NPC
        p->setHealth(npc[i]->getAnger());

        //NPC Setting
        npc[i]->setSprite();
        npc[i]->setHitbox();
        npc[i]->setActive(p->getItem(), p->getHb0(), p->getHb1());
        npc[i]->setAnger();
        npc[i]->setAngerBar();
    }

    for (unsigned int i = 0; i < 3; i++)
    {
        npcDummy[i]->setSprite();
    }

    //Items
    if (it.size() == 2)
    {
        int r_type = 6 - (it[0]->getType()) - (it[1]->getType());

        it.push_back(new Item());
        it[2]->setType(r_type);
    }

    for (unsigned int i = 0; i < it.size(); i++)
    {
        it[i]->setSprite();
        it[i]->setHitbox();
        it[i]->setActive(p->getItem(), p->getHb0(), p->getHb1());
    }

    //Trash
    t->setSprite();
    t->setHitbox();
    t->setActive(p->getItem(), p->getHb0(), p->getHb1());


    //ITEM SET ON PLAYER
    if (it.size() == 0)
    {
        p->setItemI(it[0]->getType(), it[0]->getHb0(), it[0]->getHb1(), t->isActive());
    }
    else
    {
        for (int i = 0; i < it.size(); i++)
        {
            p->setItemI(it[i]->getType(), it[i]->getHb0(), it[i]->getHb1(), t->isActive());
        }
    }

    if (npc.size() == 0)
    {
        p->setItemN(npc[0]->getType(), npc[0]->getHb0(), npc[0]->getHb1(), t->isActive());
    }
    else
    {
        for (int i = 0; i < npc.size(); i++)
        {
            p->setItemN(npc[i]->getType(), npc[i]->getHb0(), npc[i]->getHb1(), t->isActive());
        }
    }

    //RESET STATE
    if ((p->getHealth() < 0) && (enter == 1))
    {
        resetState = true;
    }
}

void gameManager::draw(sf::RenderWindow& window)
{
    if (p->getHealth() > 0)
    {
        //BG
        window.draw(bgSprite);

        //Item
        for (unsigned int i = 0; i < it.size(); i++)
        {
            if (it[i]->isActive())
            {
                window.draw(it[i]->getSprite());
            }
            else
            {
                it.erase(it.begin() + i);
            }
        };

        //NPC
        for (unsigned int i = 0; i < 3; i++)
        {
            window.draw(npcDummy[i]->getSprite());
        }

        for (unsigned int i = 0; i < npc.size(); i++)
        {
            if (npc[i]->isActive())
            {
                window.draw(npc[i]->getSprite());
                window.draw(npc[i]->getAngerBar());
                window.draw(npc[i]->getNPCText());
            }
            else
            {
                npc.erase(npc.begin() + i);
            }
        }

        //Trash
        window.draw(t->getSprite());
        window.draw(t->getTrashText());

        //Player
        window.draw(p->getSprite());
        std::vector<sf::CircleShape> healthBar = p->getHealthBar();
        for (int i = 0; i < 3; i++)
        {
            window.draw(healthBar[i]);
        }

        //Score
        window.draw(p->getScore());
    }
    else
    {
        window.draw(gameOverSprite);
        gameOverScore = p->getScore();
        gameOverScore.setPosition(675, 675);
        gameOverScore.setCharacterSize(60);
        window.draw(gameOverScore);
        window.draw(enterText);
    }
}

bool gameManager::getResetState()
{
    return resetState;
}