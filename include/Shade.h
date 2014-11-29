#ifndef __SHADE_H__
#define __SHADE_H__
#include "Player.h"
#include <string>

class Cell;

class Shade : public Player {

	public:
		Shade(Cell *cell);
		~Shade();
		void fight(Entity *against);
		void notify();
        std::string raceStr();

};

#endif