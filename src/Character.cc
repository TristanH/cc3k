#include "Character.h"
#include "Cell.h"
#include "Entity.h"

using namespace std;

Character::Character(Cell *cell, char dc, int atk, int def, int hp):
	Entity(cell, dc),
	attack(atk), defence(def), HP(hp){}

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

int Character::getDefence(){
	return defence;
}

int Character::getHP(){
	return HP;
}

void Character::changeHP(int amount){
	HP+=amount;
}
