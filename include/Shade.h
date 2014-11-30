#ifndef __SHADE_H__
#define __SHADE_H__
#include "Player.h"
#include <string>

class Cell;

class Shade : public Player {

	public:
		Shade(Cell *cell);
		~Shade();
        std::string raceStr();

};

#endif