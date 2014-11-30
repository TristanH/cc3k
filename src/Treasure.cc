#include "Treasure.h"
#include "Display.h"

Treasure::Treasure(Cell *cell, char displayChar, int value):
	Item(cell, displayChar), value(value){}
