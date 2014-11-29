#include "Treasure.h"

Treasure::Treasure(Cell *cell, char displayChar, int value):
	Item(cell, displayChar), value(value){}
