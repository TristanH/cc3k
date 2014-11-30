#include "Troll.h"
#include "Cell.h"
#include "Entity.h"
#include <string>
using namespace std;

Troll::Troll(Cell *cell) : 
	Player(cell,25,15,120) {}

Troll::~Troll() {

}

string Troll::raceStr() {
    return "Troll";
}

void Troll::gameTick() {
    HP += 5;
    if(HP > maxHP) HP = maxHP;
}