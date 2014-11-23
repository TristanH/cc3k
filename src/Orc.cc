#include "Orc.h"
#include "Cell.h"
#include "Entity.h"

Orc::Orc(Cell *cell) : 
	Enemy(cell,'O',30,25,180) {}

Orc::~Orc() {

}

void Orc::fight(Entity *against) {

}

void Orc::notify() {

}