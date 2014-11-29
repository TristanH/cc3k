#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"

class Potion: public Item{
	protected:
		int amount;

	public:
		Potion(Cell *cell, char displayChar, int amount);
		virtual bool collect(Player* player) = 0;

};

#endif
