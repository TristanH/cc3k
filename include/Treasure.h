#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "Item.h"

class Treasure: public Item{
	protected:
		int value;
	public:
		Treasure(Cell* cell, char displayChar, int value);

        // calls player->addGold(value)
		virtual bool collect(Player* player) = 0;
};

#endif
