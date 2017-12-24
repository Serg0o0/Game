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
		type = bullet_e;
		speed = 0.1;

		texture.loadFromFile("images/bullet_enemy.png");
		sprite.setTexture(texture);
	}

	if (Name == "hero")
	{
		type = bullet_h;
		speed = 0.5;

		texture.loadFromFile("images/bullet_hero.png");
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

			sprite.setPosition(posX + size_enemy / 2 - size_bul / 2, posY + size_enemy);

			if (posY >= height) 
			{
				life = false;
			}
		}

		if (Name == "hero")
		{
			dy = -speed;

			posY += dy*time;

			sprite.setPosition(posX + size_hero / 2 - size_bul / 2, posY - (4 * size_bul));

			if (posY <= 0) 
			{
				life = false;
			}
		}
	}
}