#include "Halfling.h"
#include "Cell.h"
#include "Entity.h"

Halfling::Halfling(Cell *cell) :
	Enemy(cell,'L',15,20,100) {}

Halfling::~Halfling() {

}

void Halfling::fight(Entity *against) {
	
}

void Halfling::notify() {

}