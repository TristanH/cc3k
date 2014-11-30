#ifndef __DEF_POTION_H__
#define __DEF_POTION_H__

#include "Potion.h"

class DefencePotion: public Potion{

	public:
		DefencePotion(Cell *cell, int amount);
		bool collect(Player* player);
};

#endif
