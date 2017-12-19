#include "classes.h"
#include <iostream>

Hero::Hero() 
{
	state = stay;
	hp = 100;
	posX = (weigth - size_img) / 2;
	posY = height - size_img;
	speed = 0.3;
	type = pers;
	score = 0;

	texture.loadFromFile("images/hero.png");
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
}

Enemy::Enemy()
{
	hp = 100;
	speed = 0.02;
	type = pers;
	shoot_time = 2500;

	texture.loadFromFile("images/enemy.png");
	sprite.setTexture(texture);
	sprite.setPosition(posX, posY);
	load();
}

Bullet_H::Bullet_H(float x, float y)
{
	damage = 50;
	posX = x;
	posY = y;
	type = bullet_h;
	speed = 0.5;

	texture.loadFromFile("images/bullet_hero.png");
	sprite.setTexture(texture);
}

Bullet_E::Bullet_E(float x, float y)
{
	damage = 50;
	posX = x;
	posY = y;
	type = bullet_e;
	speed = 0.1;

	texture.loadFromFile("images/bullet_enemy.png");
	sprite.setTexture(texture);
}

void Enemy::load()
{
	posX = rand() % (weigth - size_img);
	posY = 0;
}

int Bullet_H::getDamage()
{
	return damage;
}

int Bullet_E::getDamage()
{
	return damage;
}

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

void Enemy::update(float time)
{
	if (life) 
	{
		dy = speed;

		if ((posY >= 0) && (posY < (height - size_img)))
			posY += dy*time;

		if (posY >= (height - size_img)) 
		{
			posY = 0;
			posX = rand() % (weigth - size_img);
		}
		
		sprite.setPosition(posX, posY);

		if (hp <= 0)
		{ 
			life = false; 
		}
	}
}

bool Entity::shoot_delay()
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

void Bullet_H::update(float time)
{
	if (life) 
	{
		dy = -speed;

		posY += dy*time;

		sprite.setPosition(posX + size_img / 2 - size_bul / 2, posY - (4 * size_bul));

		if (posY <= 0) 
		{
			life = false;
		}
	}
}

void Bullet_E::update(float time)
{
	if (life) 
	{
		dy = speed;

		posY += dy*time;

		sprite.setPosition(posX + size_img / 2 - size_bul / 2, posY + size_img);

		if (posY >= height) 
		{
			life = false;
		}
	}
}

FloatRect Entity::getRect()
{
	if (type == pers) 
	{
		FloatRect FR(posX - size_img / 2, posY, size_img, size_img); 
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