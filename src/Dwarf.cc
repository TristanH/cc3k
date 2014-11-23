#include "Dwarf.h"
#include "Cell.h"
#include "Entity.h"

Dwarf::Dwarf(Cell *cell) :
	Enemy(cell,'d',20,30,100) {} // TODO: decide what char to use

Dwarf::~Dwarf() {

}

void Dwarf::fight(Entity *against) {

}

void Dwarf::notify() {
	
}