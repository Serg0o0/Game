// enemy.cpp
#include "enemy.h"

Enemy::Enemy()
{
	hp = 100;
	speed = 0.02;
	type = enemy;
	shootTime = 2500;

	texture.loadFromFile("images/enemy.png");
	sprite.setTexture(texture);
	load();
	load();
	sprite.setPosition(posX, posY);
}

void Enemy::load()
{
	posX = (rand() % 13) * 60 + 10; // Выбирается позиция от 10 до 790 с шагом 60
	posY = 0;
}

void Enemy::update(float time)
{
	if (life) 
	{
		dy = speed;

		if ((posY >= 0) && (posY < (height - sizeEnemy)))
			posY += dy*time;

		if (posY >= (height - sizeEnemy)) 
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

bool Enemy::shootDelay()
{
	shootTime = time.getElapsedTime().asMilliseconds();
	if (shootTime >= delay)
	{
		time.restart();
		return true;
	}
	else
		return false;
}