#ifndef __HP_POTION_H__
#define __HP_POTION_H__

#include "Potion.h"

class HealthPotion: public Potion{

	public:
		HealthPotion(Cell *cell, int amount);
		bool collect(Player* player);

};

#endif
