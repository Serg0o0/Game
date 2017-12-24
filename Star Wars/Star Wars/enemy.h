// enemy.h
#include "entity.h"

#ifndef __ENEMY_H__ 
#define __ENEMY_H__ 

class Enemy : public Entity
{
private:
	int shoot_time;
	Clock time;

public:
	Enemy();
	void update(float);
	void load();
	bool shoot_delay();
};

#endif