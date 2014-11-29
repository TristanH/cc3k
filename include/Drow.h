#ifndef __DROW_H__
#define __DROW_H__
#include "Player.h"
#include <string>

class Cell;
class Entity;

class Drow : public Player {

    public:
    	Drow(Cell *cell);
    	~Drow();
    	void fight(Entity *against);
    	void notify();
        std::string raceStr();

};

#endif