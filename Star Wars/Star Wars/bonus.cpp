// bonus.cpp
#include "bonus.h"

Bonus::Bonus(int t)
{
	speed = 0.08;
	type = bonus;
	life = false;

	if (t == 0)
	{
		timerCount = 10 + rand() % 20;
		hp = 75;

		texture.loadFromFile("images/health.png");
	}

	if (t == 1)
	{
		timerCount = 20 + rand() % 35;

		texture.loadFromFile("images/energy.png");
	}

	sprite.setTexture(texture);
	load();
	sprite.setPosition(posX, posY);
}

void Bonus::load()
{
	posX = rand() % (weigth - sizeBonus);
	posY = 0;
}

void Bonus::update(float time)
{
	if (life) 
	{
		dy = speed;
		clock.restart();

		if (posY >= 0)
			posY += dy*time;
		
		sprite.setPosition(posX, posY);

		if (posY >= (height - sizeBonus))
		{ 
			life = false; 
		}
	}
	else
	{
		load();
		timer = clock.getElapsedTime().asSeconds();
		if (timer >= timerCount)
		{
			life = true;
		}
	}
}