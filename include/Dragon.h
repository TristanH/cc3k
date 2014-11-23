#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "Enemy.h"

class Cell;
class Entity;

class Dragon : public Enemy {
    
    public:
    	Dragon(Cell *cell);
    	~Dragon();
    	void fight(Entity *against);
    	void notify();

    	// needs a specific implementation to not be aggresive
    	void updateMove();

};

#endif