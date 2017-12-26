// bullet.cpp
#include "bullet.h"

Bullet::Bullet(String name, float x, float y)
{
	Name = name;
	damage = 50;
	posX = x;
	posY = y;

	if (Name == "enemy")
	{
		type = bulletEnemy;
		speed = 0.1;

		texture.loadFromFile("images/bulletEnemy.png");
		sprite.setTexture(texture);
	}

	if (Name == "hero")
	{
		type = bulletHero;
		speed = 0.5;

		texture.loadFromFile("images/bulletHero.png");
		sprite.setTexture(texture);
	}
}

int Bullet::getDamage()
{
	return damage;
}

void Bullet::update(float time)
{
	if (life) 
	{
		if (Name == "enemy")
		{
			dy = speed;

			posY += dy*time;

			sprite.setPosition(posX + sizeEnemy / 2 - sizeBullet / 2, posY + sizeEnemy);

			if (posY >= height) 
			{
				life = false;
			}
		}

		if (Name == "hero")
		{
			dy = -speed;

			posY += dy*time;

			sprite.setPosition(posX + sizeHero / 2 - sizeBullet / 2, posY - (4 * sizeBullet));

			if (posY <= 0) 
			{
				life = false;
			}
		}
	}
}