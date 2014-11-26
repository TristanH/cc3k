#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"

class Potion: public Item{
	int amount;

	public:
		Potion(Cell *cell, int amount);

};

#endif
