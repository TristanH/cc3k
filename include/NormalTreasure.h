#ifndef __NORMAL_TREASURE_H__
#define __NORMAL_TREASURE_H__

class Player;

#include "Treasure.h"

class NormalTreasure: public Treasure{
	public:
		NormalTreasure(Cell *cell, int value);
		bool collect(Player* player);
};

#endif
