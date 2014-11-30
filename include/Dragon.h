#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "Enemy.h"

class Cell;
class Entity;
class DragonTreasure;

class Dragon : public Enemy {
    bool hostile;
    DragonTreasure *treasure;
    public:
    	Dragon(Cell *cell);
    	~Dragon();
    	void fight(Entity *against);
    	bool notify();
    	void makeHostile();
    	void setTreasure(DragonTreasure *dt);
};

#endif