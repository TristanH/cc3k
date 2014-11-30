#ifndef __ATK_POTION_H__
#define __ATK_POTION_H__

#include "Potion.h"

class AttackPotion: public Potion{

	public:
		AttackPotion(Cell *cell, int amount);
		bool collect(Player* player);
};

#endif
