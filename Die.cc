#include "Die.h"
#include "PRNG.h"

Die::Die(int numSides): numSides(numSides), sidesWithResult(){
	sides = new int[numSides];
}

void Die::addSides(int number, char result){
	if(number + sidesWithResult >= numSides){
		cerr << "Error: tried to add more sides to result than it has, returning" << endl;
		return;
	}
	for(int i=0; i < number; i++){
		sides[sidesWithResult] = result;
		sidesWithResult++;
	}
}

char rollDie(){
	if(number + sidesWithResult >= numSides){
		cerr << "Error: tried to roll die without filling all the sides" << endl;
		return 0;
	}
	prng random(time(NULL));
	int sideChosen = random(numSides);
	return sides[sideChosen];
}

Die::~Die(){
	delete sides;
}
