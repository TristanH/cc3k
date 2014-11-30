#include "Dragon.h"
#include "Cell.h"
#include "Player.h"
#include "DragonTreasure.h"
#include "Display.h"

#include <iostream>

using namespace std;

Dragon::Dragon(Cell *cell):
	Enemy(cell, 'D', 20, 20, 150), treasure(NULL){}

Dragon::~Dragon() {
	
}

void Dragon::fight(Entity *against) {

}

bool Dragon::notify() {
	cerr << "got to dragon notify" << endl;
	if(HP <= 0){
		Display::statusMessage+="D has been killed! ";
		cerr << "wrote display message" << endl;
		cell->setEntity(NULL);
		cerr <<"removed entity"<<endl;
		treasure->dragonDead();
		cerr <<"told dragon dead"<<endl;
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
	cerr << "set dragon treasure!!" << endl;
}