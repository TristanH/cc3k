#include "Character.h"
#include "Cell.h"
#include "Entity.h"
#include "Player.h"

using namespace std;

string Character::dirFull(string shortDir) {
	if(shortDir == "no") {
		return "North";
	} else if(shortDir == "ea") {
		return "East";
	} else if(shortDir == "so") {
		return "South";
	} else if(shortDir == "we") {
		return "West";
	} else if(shortDir == "ne") {
		return "North-East";
	} else if(shortDir == "nw") {
		return "North-West";
	} else if(shortDir == "se") {
		return "South-East";
	} else if(shortDir == "sw") {
		return "South-West";
	}
}

Character::Character(Cell *cell, char dc, int atk, int def, int hp):
	Entity(cell, dc),
	attack(atk), defence(def), HP(hp){}

bool Character::tryMove(string direction){
	Cell *theCell = getCell();
	Cell *goTo = theCell->getAdjacentCell(direction);
	Player *p = dynamic_cast<Player *>(this);
	if (goTo->isWalkable(p != NULL)){
		theCell->setEntity(NULL);
		goTo->setEntity(this);
		#ifdef DEBUG
		//cout << "Character: able to move to that cell" << endl;
		#endif
		return true;
	}
	else {
		#ifdef DEBUG
		//cout << "Character: unable to move to that cell" << endl;
		#endif

		return false;
	}

}

int Character::getDefence(){
	return defence;
}

int Character::getAttack() {
	return attack;
}

int Character::getHP(){
	return HP;
}

void Character::changeHP(int amount){
	HP+=amount;
}
