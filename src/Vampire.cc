#include "Vampire.h"
#include "Cell.h"
#include "Entity.h"
#include <string>
using namespace std;

Vampire::Vampire(Cell *cell) :
	Player(cell,25,25,50) {}

Vampire::~Vampire() {

}

void Vampire::fight(Entity *against) {

}

string Vampire::raceStr() {
    return "Vampire";
}