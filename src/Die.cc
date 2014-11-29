#include "Die.h"
#include "PRNG.h"

#include <iostream>

using namespace std;

Die::Die(int numSides): numSides(numSides), sidesWithResult(0){
	sides = new int[numSides];
}

void Die::addSides(int number, char result){
	if(number + sidesWithResult > numSides){
		cerr << "Error: tried to add more sides to result than it has, returning" << endl;
		return;
	}
	for(int i=0; i < number; i++){
		sides[sidesWithResult] = result;
		sidesWithResult++;
	}
	#ifdef DEBUG
		cout << "Sides of die covered: " << sidesWithResult << " of " <<numSides << endl;
	#endif
}

char Die::rollDie(){
	if(sidesWithResult < numSides){
		cerr << "Error: tried to roll die without filling all the sides" << endl;
		return 0;
	}
	int sideChosen = PRNG::random(numSides - 1);
	return sides[sideChosen];
}

Die::~Die(){
	delete[] sides;
}
