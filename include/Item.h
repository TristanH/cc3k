#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"

class Player;

class Item: public Entity{
	
	public:
		Item(Cell *cell, char displayChar);
		// returns true if it was able to be collected
		virtual bool collect(Player* player) = 0;
};

#endif
