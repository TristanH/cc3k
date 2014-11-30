#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"

class Potion: public Item{
	protected:
		int amount;
		static bool visible[6];

	public:
		Potion(Cell *cell, char displayChar, int amount);
		virtual bool collect(Player* player) = 0;
		static void setPotionsVisible(char displayChar);
		char getDisplayChar();

};

#endif
