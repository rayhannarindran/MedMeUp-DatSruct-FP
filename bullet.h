#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"

class Bullet : public Entity
{
private:
	bool active;
	float rotated_x, rotated_y;

public:
	Bullet();
	~Bullet();
	void setSprite();
	void setHitbox();
	void setActive(bool state);
	bool getActive();
	void Move(float angle);
};

