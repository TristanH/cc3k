#ifndef __SHADE_H__
#define __SHADE_H__
#include "Player.h"

class Cell;

class Shade : public Player {

	public:
		Shade(Cell *cell);
		~Shade();
		void fight(Entity *against);
		void notify();

};

#endif