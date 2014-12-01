#include "Potion.h"
#include "Drow.h"
#include "Floor.h"
#include <iostream>

using namespace std;

bool Potion::visible[6] = {false, false, false, false, false, false};

Floor* Potion::floor = NULL;

Potion::Potion(Cell *cell, char displayChar, int amount):
	Item(cell, displayChar), amount(amount){}

void Potion::setPotionsVisible(char displayChar){
	visible[displayChar - '0'] = true;
	if(floor)
		floor->updatePotions();
	else{
		;
		#ifdef DEBUG
		cerr << "Potion doesn't have a floor, cant update all potions!!" << endl;
		#endif
	}
}

char Potion::getDisplayChar(){
	if(visible[this->getMapChar() - '0'])
		return this->getMapChar();
	else
		return 'P';
}

bool Potion::collect(Player *player) {
    if(dynamic_cast<Drow *>(Player::getInstance())) amount *= 1.5;
    Player::addPotion(getMapChar(), amount);
}

void Potion::setFloor(Floor *f){
	Potion::floor = f;
}
