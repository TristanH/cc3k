#include "Goblin.h"
#include "Cell.h"
#include "Entity.h"
#include <string>
using namespace std;


Goblin::Goblin(Cell *cell) : 
	Player(cell,15,20,110) {}

Goblin::~Goblin() {

}

string Goblin::raceStr() {
    return "Goblin";
}