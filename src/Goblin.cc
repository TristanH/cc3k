#include "Goblin.h"
#include "Cell.h"
#include "Entity.h"
#include <string>

Goblin::Goblin(Cell *cell) : 
	Player(cell,15,20,110) {}

Goblin::~Goblin() {

}

void Goblin::fight(Entity *against) {

}

void Goblin::notify() {
	// what should we do with dis?
}

string Goblin::raceStr() {
    return "Goblin";
}