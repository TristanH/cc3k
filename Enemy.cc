#include "Enemy.h"
#include "Cell.h"
#include "Player.h"

using namespace std;

void Enemy::updateMove(){

	//check block radius for player to fight
	Player *player = cell.findPlayerInBounds();
	if(player != NULL){
		// combat here
		//fight(player);
		return;
	}

	// choose random directions until we find one 
	// that we can move to
	string tryDirection;
	//currently numChecks is just a cheap dirty trick to avoid infinite loops
	int numChecks = 0;
	do{
		tryDirection = Cell::getRandomDirection();
		numChecks++;
	}while(!tryMove(tryDirection) && numChecks <= 1000);
}
