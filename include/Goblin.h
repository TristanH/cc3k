#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "Player.h"
#include <string>

class Cell;
class Entity;
    
class Goblin : public Player {

    public:
    	Goblin(Cell *cell);
    	~Goblin();
    	void fight(Entity *against);
        std::string raceStr();

};

#endif