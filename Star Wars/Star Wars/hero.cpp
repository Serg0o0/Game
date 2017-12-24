// hero.cpp
#include "hero.h"

Hero::Hero() 
{
	size_hero = 50;
	state = stay;
	hp = 100;
	posX = (weigth - size_hero) / 2;
	posY = height - size_hero;
	speed = 0.3;
	type = hero;
	score = 0;
	armor = false;

	texture.loadFromFile("images/hero.png");
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
}

void Hero::update(float time)
{
	if (life)
	{
		control();
		switch (state)
		{
		case right: 
			dx = speed; 
			break; 
		case left: 
			dx = -speed; 
			break;
		case up: 
			dy = -speed; 
			break;
		case down: 
			dy = speed; 
			break;
		case stay:
			dx = 0;
			dy = 0;
			break;
		default:
			break;
		}

		if ((posX > 0) && (dx < 0)) 
			posX += dx*time;

		if ((posX < (weigth - size_hero)) && (dx > 0)) 
			posX += dx*time;

		if ((posY > (2 * height / 3)) && (dy < 0)) 
			posY += dy*time;

		if ((posY < (height - size_hero)) && (dy > 0)) 
			posY += dy*time;

		state = stay;
		sprite.setPosition(posX, posY);

		if (hp <= 0)
		{ 
			hp = 0;
			life = false; 
		}

		if (armor)
		{
			texture.loadFromFile("images/armor.png");
			sprite.setTexture(texture, true);
			size_hero = 60;
		}
		else
		{
			texture.loadFromFile("images/hero.png");
			sprite.setTexture(texture, true);
			size_hero = 50;
		}

		if (armor_hp <= 0)
		{ 
			armor_hp = 0;
			armor = false; 
		}
	}
}

void Hero::control()
{ 
	if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A))) 
	{ 
		state = left; 
	} 
	
	if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D))) 
	{ 
		state = right; 
	} 
	
	if ((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W))) 
	{ 
		state = up; 
	} 
	
	if ((Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S))) 
	{ 
		state = down; 
	} 
}

bool Hero::getArmor()
{
	return armor;
}

int Hero::getArmor_HP()
{
	return armor_hp;
}

void Hero::setArmor(bool a)
{
	armor = a;
	armor_hp = 300;
	if (!getArmor())
	{
		posX -= 5;
		posY -= 10;
	}
}

void Hero::setArmor(int a)
{
	armor_hp += a;
}