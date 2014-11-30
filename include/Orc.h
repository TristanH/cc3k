#ifndef __ORC_H__
#define __ORC_H__
#include "Enemy.h"

class Cell;
class Entity;

class Orc : public Enemy {

    public:
    	Orc(Cell *cell);
    	~Orc();
    	void fight(Entity *against);
    	int specialFightEffect(Character *against, int damageDone);
};

#endif