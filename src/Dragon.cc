#include "Dragon.h"

Dragon::Dragon(Cell *cell, DragonTreasure* dt): 
	treasure(dt), displayChar('D'), cell(cell), attack(20),
	defence(20), HP(150){}

void Dragon::updateMove(){
	;//do nothing
}

