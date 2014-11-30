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
    if(against->getDisplayChar() == 'd')
    	Display::statusMessage+="Player lost additional 5 HP from fighting a dwarf. ";
    else
    	Display::statusMessage+="Player gained additional 5 HP. ";
}

string Vampire::raceStr() {
    return "Vampire";
}