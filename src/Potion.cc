#include "Potion.h"

Potion::Potion(Cell *cell, int amount):
	Item(cell, 'P'), amount(amount){}