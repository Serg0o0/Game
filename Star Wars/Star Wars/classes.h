#include "SFML/Graphics.hpp"
#include "globals.h"
using namespace sf;

#ifndef __CLASSES_H__ 
#define __CLASSES_H__ 

class Entity
{
protected:
	int hp, score, shoot_time;
	Clock time;
	bool life;
	float speed, dx, dy, posX, posY;
	enum { left, right, up, down, stay } state;
	enum { pers, bullet } type;
	std::string name;
	Texture texture;
	Sprite sprite;

public:
	Sprite getimage();
	FloatRect getRect();
	virtual void update(float) = 0;
	int getHP();
	void setHP(int);
	float getposX();
	float getposY();
	bool getLife();
	void setLife(bool);
	void setScore(int);
	int getScore();
	bool shoot_delay();
};

class Hero : public Entity
{
public:
	Hero();
	void update(float);
	void control();
};

class Enemy : public Entity
{
public:
	Enemy();
	void update(float);
};

class Bullet_H : public Entity
{
private:
	int damage;

public:
	Bullet_H(float, float);
	void update(float);
	int getDamage();
};

class Bullet_E : public Entity
{
private:
	int damage;

public:
	Bullet_E(float, float);
	void update(float);
	int getDamage();
};

 #endif