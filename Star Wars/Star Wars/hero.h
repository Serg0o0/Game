// hero.h
#include "entity.h"

#ifndef __HERO_H__ 
#define __HERO_H__ 

class Hero : public Entity
{
private:
	bool armor;
	int armorHp;

public:
	Hero();
	void update(float);
	void control();
	bool getArmor();
	int getArmorHp();
	void setArmor(bool);
	void setArmor(int);
};

#endif