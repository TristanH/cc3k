#include "Potion.h"

#include <iostream>

using namespace std;

bool Potion::visible[6] = {false, false, false, false, false, false};

Potion::Potion(Cell *cell, char displayChar, int amount):
	Item(cell, displayChar), amount(amount){}

void Potion::setPotionsVisible(char displayChar){
	visible[displayChar - '0'] = true;
}

char Potion::getDisplayChar(){
	cout << "hit potion::getdisplaychar";
	if(visible[this->getMapChar() - '0'])
		return this->getMapChar();
	else
		return 'P';
}


