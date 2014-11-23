#ifndef __DROW_H__
#define __DROW_H__
#include "Player.h"

class Cell;
class Entity;

class Drow : public Player {

    public:
    	Drow(Cell *cell);
    	~Drow();
    	void fight(Entity *against);
    	void notify();

};

#endif