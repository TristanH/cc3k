#include "Character.h"

using namespace std;

bool Character::tryMove(string direction){
	Cell *goTo = cell->getAdjacentCell(direction);
	if (cell->isWalkable()){
		cell->setEntity(NULL);
		goTo->setEntity(this);
		return true;
	}
	else
		return false;

}
