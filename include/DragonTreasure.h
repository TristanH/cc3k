#ifndef __DRAGON_TREASURE_H__
#define __DRAGON_TREASURE_H__

class Player;
class Dragon;

#include "Treasure.h"

class DragonTreasure: public Treasure{
	
	Dragon* dragon;

	public:
		DragonTreasure(Cell *cell, int value, Dragon *dragon);
		// only returns true if the dragon is dead eg NULL
		bool collect(Player* player);
		Dragon *getDragon();
		void dragonDead();
		void setDragon(Dragon *d);
};

#endif
