#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "Item.h"

class Treasure: public Item{
	// all treasures will be concrete instances of this class except for DragonTreasures
	int value;
	public:
		Treasure(int value);
		bool collect(Player* player);
};

#endif
