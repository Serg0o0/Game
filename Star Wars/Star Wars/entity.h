// entity.h
#include "SFML/Graphics.hpp"
#include "globals.h"
using namespace sf;

#ifndef __ENTITY_H__ 
#define __ENTITY_H__ 

class Entity
{
protected:
	int hp, score;
	bool life;
	float speed, dx, dy, posX, posY;
	enum { left, right, up, down, stay } state;
	enum { enemy, hero, bonus, bullet_e, bullet_h } type;
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
};

#endif