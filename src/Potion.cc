#include "Potion.h"

Potion::Potion(Cell *cell, char displayChar, int amount):
	Item(cell, displayChar), amount(amount){}