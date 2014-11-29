#include "Shade.h"
#include "Cell.h"
#include "Entity.h"
#include <string>
using namespace std;

Shade::Shade(Cell *cell) : 
	Player(cell, 25, 25, 125) {}

Shade::~Shade(){

}

void Shade::fight(Entity *against) {

}

void Shade::notify() {
	// what should we do with dis?
}

string Shade::raceStr() {
    return "Shade";
}