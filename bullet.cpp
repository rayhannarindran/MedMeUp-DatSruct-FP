#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Bullet::Bullet()
{
	scale = 0.075;
	position = sf::Vector2f(500, 500);
	rotated_x = this->getPosition().x;
	rotated_y = this->getPosition().y;
}

Bullet::~Bullet()
{

}

void Bullet::setSprite()
{
	texture.loadFromFile("sprites/bullet.png");
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	sprite.setPosition(position);
}

void Bullet::setHitbox()
{
	hitbox.setSize(sf::Vector2f(27, 45));
	hitbox.setPosition(position.x, position.y + 45);
	hb0 = hitbox.getTransform().transformPoint(hitbox.getPoint(0));
	hb1 = hitbox.getTransform().transformPoint(hitbox.getPoint(2));
}



void Bullet::setActive(bool state)
{
	active = state;
}

bool Bullet::getActive()
{
	return active;
}

//CHECK HERE!!!
void Bullet::Move(float angle)
{
	this->setRotation(angle);
	
	if (angle != 0)
	{
		rotated_x = (this->getPosition().x * cos(angle)) - (this->getPosition().y * sin(angle));
		rotated_y = (this->getPosition().x * sin(angle)) + (this->getPosition().y * cos(angle));
		//this->setPosition(this->getPosition().x + rotated_x)
	}
	
}