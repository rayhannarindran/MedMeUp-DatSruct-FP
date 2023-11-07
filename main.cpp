//DEFAULT AND SFML LIBRARIES
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//INCLUDE LIBRARIES
#include "game.h"

//NAMESPACES
using namespace std;
using namespace sf;

int main()
{
    //INITS
    int WIDTH = 1600;
    int LENGTH = 900;
    string GAME_NAME = "Med Me Up!";
    sf::Image icon;
    icon.loadFromFile("sprites/GameIcon.jpg");

    RenderWindow window(VideoMode(WIDTH, LENGTH), GAME_NAME);
    window.setFramerateLimit(60);
    window.setIcon(226, 226, icon.getPixelsPtr());
    Event ev;

    reset:
    gameManager GM;

    //Game Start
    GM.start();

    while (window.isOpen())
    {
        //EVENTS (Key Presses, Mouse Movement, etc)
        while (window.pollEvent(ev))
        {
            GM.event(ev);
            switch (ev.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                switch (ev.key.code)
                {
                case Keyboard::Escape:
                    window.close();
                    break;
                };
                break;
            };
        }

        //UPDATING--------------------------
        window.clear();

        //GAMEPLAY-----------------------
        GM.update();

        //cout << "reset state: " << GM.getResetState() << endl;

        //DRAWS
        GM.draw(window);

        //DISPLAYING-----------------------
        window.display();

        //CHECKING STATE----------------
        if (GM.getResetState() == true)
        {
            goto reset;
        }
    }

    return 0;
}