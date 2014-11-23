#include "Shade.h"
#include "Cell.h"
#include "Entity.h"

Shade::Shade(Cell *cell) : 
	Player(cell, 25, 25, 125) {}

Shade::~Shade(){

}

void Shade::fight(Entity *against) {

}

void Shade::notify() {
	// what should we do with dis?
}