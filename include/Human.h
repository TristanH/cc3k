#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "Enemy.h"

class Cell;
class Entity;

class Human : public Enemy {

    public:
    	Human(Cell *cell);
    	~Human();
    	void fight(Entity *against);
    	void onDeath();
};

#endif