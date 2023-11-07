#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"

class Trash : public Entity
{
private:
	bool active;
	sf::Font trashFont;
	sf::Text trashText;

public:
	Trash();
	~Trash();
	void setSprite();
	void setHitbox();
	void setActive(int pItem, sf::Vector2f phb0, sf::Vector2f phb1);
	bool isActive();
	sf::Text getTrashText();
};

