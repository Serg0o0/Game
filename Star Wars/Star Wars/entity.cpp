// entity.cpp
#include "entity.h"

Sprite Entity::getImage()
{
	return sprite;
}

bool Entity::getLife()
{
	return life;
}

void Entity::setLife(bool l)
{
	life = l;
	if (l)
	{
		hp = 100;
	}
}

void Entity::setScore(int s)
{
	score += s;
}

int Entity::getScore()
{
	return score;
}

int Entity::getHP()
{
	return hp;
}

void Entity::setHP(int h)
{
	hp += h;
}

float Entity::getPosX()
{
	return posX;
}

float Entity::getPosY()
{
	return posY;
}

FloatRect Entity::getRect()
{
	if (type == enemy) 
	{
		FloatRect FR(posX - sizeEnemy / 2, posY, sizeEnemy, sizeEnemy); 
		return FR;
	}

	if (type == hero) 
	{
		if (sizeHero == 50)
		{
			FloatRect FR(posX - sizeHero / 2, posY, sizeHero, sizeHero); 
			return FR;
		}
		else
		{
			FloatRect FR(posX - sizeHero / 2 + 10, posY, sizeHero, sizeHero); 
			return FR;
		}
	}

	if (type == bonus) 
	{
		FloatRect FR(posX - sizeBonus / 2, posY, sizeBonus, sizeBonus); 
		return FR;
	}

	if (type == bulletEnemy) 
	{
		FloatRect FR(posX, posY + 10 * sizeBullet, sizeBullet, 4 * sizeBullet); 
		return FR;
	}

	if (type == bulletHero) 
	{
		FloatRect FR(posX, posY, sizeBullet, 4 * sizeBullet); 
		return FR;
	}
	
}