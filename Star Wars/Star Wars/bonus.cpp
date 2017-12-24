// bonus.cpp
#include "bonus.h"

Bonus::Bonus(int t)
{
	speed = 0.08;
	type = bonus;
	life = false;

	if (t == 0)
	{
		timer_count = 10 + rand() % 20;
		hp = 75;

		texture.loadFromFile("images/health.png");
	}

	if (t == 1)
	{
		timer_count = 15 + rand() % 30;

		texture.loadFromFile("images/energy.png");
	}

	sprite.setTexture(texture);
	load();
	sprite.setPosition(posX, posY);
}

void Bonus::load()
{
	posX = rand() % (weigth - size_bonus);
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

		if (posY >= (height - size_bonus))
		{ 
			life = false; 
		}
	}
	else
	{
		load();
		timer = clock.getElapsedTime().asSeconds();
		if (timer >= timer_count)
		{
			life = true;
		}
	}
}