#include "SFML/Graphics.hpp"
#include "globals.h"
using namespace sf;

#ifndef __CLASSES_H__ 
#define __CLASSES_H__ 

class Hero
{
protected:
	int hp, dir;
	bool life;
	float speed, dx, dy, posX, posY;
	enum {left, right, up, down, stay } state;
	Texture texture;
	Sprite sprite;
		
public:
	Hero();
	Sprite getimage();
	void update(float);
	int getHP();
	float getposX();
	float getposY();
	void setDir(int);
	void setSpeed(float);
	void control();
};

class Enemy : public Hero
{
public:
	Enemy();
};

class Bullet
{
private:
	int damage;
	float posX, posY;
	Texture texture;
	Sprite sprite;

public:
	Bullet();
	Sprite getimage();
	int hit(int);
	void setSpeed(float);
};

 #endif