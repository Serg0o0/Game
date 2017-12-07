#include "classes.h"

Hero::Hero() 
{
	state = stay;
	hp = 100;
	posX = (weigth - size_img) / 2;
	posY = height - size_img;
	dir = 0;
	speed = 0.3;

	texture.loadFromFile("images/hero.png");
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
}

Enemy::Enemy()
{
	hp = 100;
	posX = (weigth - size_img) / 2;
	posY = height - size_img;

	texture.loadFromFile("images/enemy.png");
	sprite.setTexture(texture);
	sprite.setPosition(posX, 0);
}

Bullet::Bullet()
{
	damage = 50;
	posX = 400;
	posY = 300;

	texture.loadFromFile("images/bullet_hero.png");
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
}

Sprite Hero::getimage()
{
	return sprite;
}

Sprite Bullet::getimage()
{
	return sprite;
}

int Hero::getHP()
{
	return hp;
}

float Hero::getposX()
{
	return posX;
}

float Hero::getposY()
{
	return posY;
}

void Hero::update(float time)
{
	if (life)
	{
		control();
		//dx = 0;
		//dy = 0;
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

		if ((posX < (weigth - size_img)) && (dx > 0)) 
			posX += dx*time;

		if ((posY > (2 * height / 3)) && (dy < 0)) 
			posY += dy*time;

		if ((posY < (height - size_img)) && (dy > 0)) 
			posY += dy*time;

		state = stay;
		sprite.setPosition(posX, posY);

		if (hp <= 0)
		{ 
			life = false; 
		}
	}
}

void Hero::setDir(int d)
{
	dir = d;
}

void Hero::setSpeed(float s)
{
	speed = s;
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