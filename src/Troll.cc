#include "Troll.h"
#include "Cell.h"
#include "Entity.h"
#include <string>
using namespace std;

Troll::Troll(Cell *cell) : 
	Player(cell,25,15,120) {}

Troll::~Troll() {

}

void Troll::fight(Entity *against) {

}

void Troll::notify() {
	// what should we do with dis?
}

string Troll::raceStr() {
    return "Troll";
}