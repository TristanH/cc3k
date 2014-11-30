#include "Dragon.h"
#include "Cell.h"

Dragon::Dragon(Cell *cell):
	Enemy(cell, 'D', 20, 20, 150){}

Dragon::~Dragon() {
	
}

void Dragon::fight(Entity *against) {

}

bool Dragon::notify() {
	return true;
}

void Dragon::updateMove(){
	;//do nothing
}

