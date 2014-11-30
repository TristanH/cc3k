#ifndef __POTION_H__
#define __POTION_H__

#include "Item.h"

class Floor;

class Potion: public Item{
	protected:
		int amount;
		static bool visible[6];
		static Floor* floor;

	public:
		Potion(Cell *cell, char displayChar, int amount);
		virtual bool collect(Player* player);
		static void setPotionsVisible(char displayChar);
		char getDisplayChar();
		static void setFloor(Floor *f);

};

#endif
