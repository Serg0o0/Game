// bullet.h
#include "entity.h"

#ifndef __BULLET_H__ 
#define __BULLET_H__ 

class Bullet : public Entity
{
private:
	int damage;
	String Name;

public:
	Bullet(String, float, float);
	void update(float);
	int getDamage();
};

#endif