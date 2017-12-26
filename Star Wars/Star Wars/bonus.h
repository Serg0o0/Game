// bonus.h
#include "entity.h"

#ifndef __BONUS_H__ 
#define __BONUS_H__ 

class Bonus : public Entity
{
private:
	int timer, timerCount;
	Clock clock;

public:
	Bonus(int);
	void update(float);
	void load();
};

#endif