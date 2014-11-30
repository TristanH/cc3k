#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "Player.h"
#include <string>

class Cell;
class Entity;

class Vampire : public Player {
	public:
		Vampire(Cell *cell);
		~Vampire();
		void fight(Entity *against);
        std::string raceStr();
};

#endif