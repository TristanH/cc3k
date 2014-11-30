#include "Character.h"
#include "Cell.h"
#include "Entity.h"
#include "Player.h"
#include "Item.h"

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

Character::Character(Cell *cell, char dc, int atk, int def, int hp, int maxHP):
	Entity(cell, dc),
	attack(atk), defence(def), HP(hp) {
		// this is so we can force set maxHP when decorating a player, otherwise it defaults to -1 and just becomes HP
		if(maxHP < 0) {
			#ifdef DEBUG
			cout << "maxHP not defined. Defining to be HP" << endl;
			cout << maxHP;
			#endif
			this->maxHP = hp;
		} else {
			#ifdef DEBUG
			cout << "maxHP defined: " << maxHP << endl;
			#endif
			this->maxHP = maxHP;
		}
	}

bool Character::tryMove(string direction){
	Cell *theCell = getCell();
	Cell *goTo = theCell->getAdjacentCell(direction);
	Player *p = dynamic_cast<Player *>(this);
	if (goTo->isWalkable(p != NULL)){
		/* old gold pickup logic
		if(p && goTo->getType() == 'G') {
			Item *item = dynamic_cast<Item *>(goTo->getEntity());
			item->collect(p);
		}
		*/
		theCell->setEntity(NULL);
		goTo->setEntity(this);
		return true;
	}
	else {
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

int Character::getMaxHP() {
	return maxHP;
}

void Character::changeHP(int amount){
	HP+=amount;
}
