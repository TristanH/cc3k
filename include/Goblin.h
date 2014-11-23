#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "Player.h"

class Cell;
class Entity;
    
class Goblin : public Player {

    public:
    	Goblin(Cell *cell);
    	~Goblin();
    	void fight(Entity *against);
    	void notify();

};

#endif