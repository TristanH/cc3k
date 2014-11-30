#include "Vampire.h"
#include "Cell.h"
#include "Entity.h"
#include "Display.h"
#include <string>
using namespace std;

Vampire::Vampire(Cell *cell) :
	Player(cell,25,25,50) {}

Vampire::~Vampire() {

}

void Vampire::fight(Entity *against) {
    Player::fight(against);
    HP += 5;
    Display::statusMessage+="Player gained additional 5 HP. ";
}

string Vampire::raceStr() {
    return "Vampire";
}