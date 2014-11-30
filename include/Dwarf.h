#ifndef __DWARF_H__
#define __DWARF_H__

#include "Enemy.h"

class Cell;
class Entity;

class Dwarf : public Enemy {

    public:
    	Dwarf(Cell *cell);
    	~Dwarf();
    	void fight(Entity *against);
};

#endif