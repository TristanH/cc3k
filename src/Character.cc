#include "Character.h"
#include "Cell.h"

using namespace std;

bool Character::tryMove(string direction){
	Cell *theCell = getCell();
	Cell *goTo = theCell->getAdjacentCell(direction);
	if (theCell->isWalkable()){
		theCell->setEntity(NULL);
		goTo->setEntity(this);
		return true;
	}
	else
		return false;

}
