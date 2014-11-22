#include "Dragon.h"
#include "Cell.h"

Dragon::Dragon(Cell *cell):
	Enemy(cell, 'D', 20, 20, 150){}

void Dragon::updateMove(){
	;//do nothing
}

