#include "Dragon.h"
#include "Cell.h"

Dragon::Dragon(Cell *cell):
	Enemy(cell, 'D', 20, 20, 150){}

Dragon::~Dragon() {
	
}

void Dragon::fight(Entity *against) {

}

void Dragon::notify() {
	
}

void Dragon::updateMove(){
	;//do nothing
}

