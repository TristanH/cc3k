#include "Dragon.h"
#include "Cell.h"
#include "Player.h"
#include "DragonTreasure.h"
#include "Display.h"

#include <iostream>

using namespace std;

Dragon::Dragon(Cell *cell):
	Enemy(cell, 'D', 20, 20, 150), treasure(NULL), hostile(false){}

Dragon::~Dragon() {
	
}

void Dragon::fight(Entity *against) {
	Enemy::fight(against);
}

bool Dragon::notify() {
	#ifdef DEBUG
	cerr << "notifying dragon! " << hostile << endl;
	#endif
	if(HP <= 0){
		Display::statusMessage+="D has been killed! ";
		cell->setEntity(NULL);
		treasure->dragonDead();
		return false;
	}
	if(hostile){
		fight(Player::getInstance());
	}
	return true;
}

void Dragon::makeHostile(){
	hostile = true;
}

void Dragon::setTreasure(DragonTreasure* dt){
	treasure = dt;
}