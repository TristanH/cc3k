#include "Dragon.h"
#include "Cell.h"

Dragon::Dragon(Cell *cell):
	displayChar('D'), cell(cell), attack(20),
	defence(20), HP(150){}

void Dragon::updateMove(){
	;//do nothing
}

