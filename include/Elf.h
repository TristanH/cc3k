#ifndef __ELF_H__
#define __ELF_H__

#include "Enemy.h"

class Cell;
class Entity;

class Elf : public Enemy {

    public:
    	Elf(Cell* cell);
    	~Elf();
    	void fight(Entity *against);
};

#endif