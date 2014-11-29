#include "Vampire.h"
#include "Cell.h"
#include "Entity.h"
#include <string>

Vampire::Vampire(Cell *cell) :
	Player(cell,25,25,50) {}

Vampire::~Vampire() {

}

void Vampire::fight(Entity *against) {

}

void Vampire::notify() {

}

string Vampire::raceStr() {
    return "Vampire";
}