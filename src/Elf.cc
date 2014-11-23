#include "Elf.h"
#include "Cell.h"
#include "Entity.h"

Elf::Elf(Cell* cell):
	Enemy(cell, 'E', 30, 10, 140){}

Elf::~Elf() {

}

void Elf::fight(Entity *against) {

}

void Elf::notify() {
	
}