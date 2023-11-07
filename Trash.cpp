#include "trash.h"
#include <SFML/Graphics.hpp>

Trash::Trash()
{
	scale = 0.045;
	position = sf::Vector2f(150, 350);
	sprite.setOrigin(570, 580);
	active = false;

	trashFont.loadFromFile("sprites/ARLRDBD.TTF");
	trashText.setFont(trashFont);
	trashText.setString("Trash");
	trashText.setCharacterSize(20);
	trashText.setFillColor(sf::Color::White);
	trashText.setOutlineThickness(3);
	trashText.setOutlineColor(sf::Color::Black);
	trashText.setPosition(position.x - 23, position.y + 40);
};

Trash::~Trash()
{

};

void Trash::setSprite()
{
	texture.loadFromFile("sprites/TRASH.png");
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	sprite.setPosition(position);
};

void Trash::setHitbox()
{
	hitbox.setSize(sf::Vector2f(70, 68));
	hitbox.setPosition(position.x - 5, position.y - 5);
	hb0 = hitbox.getTransform().transformPoint(hitbox.getPoint(0));
	hb1 = hitbox.getTransform().transformPoint(hitbox.getPoint(2));
}

void Trash::setActive(int pItem, sf::Vector2f phb0, sf::Vector2f phb1)
{
	if ((pItem != 0) && (hb0.x < phb1.x && hb0.y < phb1.y) && (hb1.x > phb0.x && hb1.y > phb0.y))
	{
		active = true;
	}
	else
	{
		active = false;
	}
};

bool Trash::isActive()
{
	return active;
}

sf::Text Trash::getTrashText()
{
	return trashText;
}
