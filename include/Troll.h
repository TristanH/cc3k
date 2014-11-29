#ifndef __TROLL_H__
#define __TROLL_H__
#include "Player.h"
#include <string>

class Cell;
class Entity;

class Troll : public Player {

	public:
		Troll(Cell *cell);
		~Troll();
		void fight(Entity *against);
		void notify();
        std::string raceStr();

};

#endif