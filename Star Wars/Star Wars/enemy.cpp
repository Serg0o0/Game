// enemy.cpp
#include "enemy.h"

Enemy::Enemy()
{
	hp = 100;
	speed = 0.02;
	type = enemy;
	shoot_time = 2500;

	texture.loadFromFile("images/enemy.png");
	sprite.setTexture(texture);
	load();
	load();
	sprite.setPosition(posX, posY);
}

void Enemy::load()
{
	posX = rand() % (weigth - size_enemy);
	posY = 0;
}

void Enemy::update(float time)
{
	if (life) 
	{
		dy = speed;

		if ((posY >= 0) && (posY < (height - size_enemy)))
			posY += dy*time;

		if (posY >= (height - size_enemy)) 
		{
			load();
		}
		
		sprite.setPosition(posX, posY);

		if (hp <= 0)
		{ 
			life = false; 
			load();
		}
	}
}

bool Enemy::shoot_delay()
{
	shoot_time = time.getElapsedTime().asMilliseconds();
	if (shoot_time >= delay)
	{
		time.restart();
		return true;
	}
	else
		return false;
}