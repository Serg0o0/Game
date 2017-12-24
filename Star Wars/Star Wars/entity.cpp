// entity.cpp
#include "entity.h"

Sprite Entity::getimage()
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

float Entity::getposX()
{
	return posX;
}

float Entity::getposY()
{
	return posY;
}

FloatRect Entity::getRect()
{
	if (type == enemy) 
	{
		FloatRect FR(posX - size_enemy / 2, posY, size_enemy, size_enemy); 
		return FR;
	}

	if (type == hero) 
	{
		if (size_hero == 50)
		{
			FloatRect FR(posX - size_hero / 2, posY, size_hero, size_hero); 
			return FR;
		}
		else
		{
			FloatRect FR(posX - size_hero / 2 + 10, posY, size_hero, size_hero); 
			return FR;
		}
	}

	if (type == bonus) 
	{
		FloatRect FR(posX - size_bonus / 2, posY, size_bonus, size_bonus); 
		return FR;
	}

	if (type == bullet_e) 
	{
		FloatRect FR(posX, posY + 10 * size_bul, size_bul, 4 * size_bul); 
		return FR;
	}

	if (type == bullet_h) 
	{
		FloatRect FR(posX, posY, size_bul, 4 * size_bul); 
		return FR;
	}
	
}