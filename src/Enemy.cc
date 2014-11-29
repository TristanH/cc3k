#include "Enemy.h"
#include "Cell.h"
#include "Player.h"

using namespace std;

void Enemy::move() {
	// choose random directions until we find one 
	// that we can move to
	string tryDirection;
	//currently numChecks is just a cheap dirty trick to avoid infinite loops
	int numChecks = 0;
	do{
		tryDirection = Cell::getRandomDirection();
		numChecks++;
	}while(!tryMove(tryDirection) && numChecks <= 1000);
	#ifdef DEBUG
	cout << "Enemy: " << *this << ": " << tryDirection << endl;
	#endif
}

Enemy::Enemy(Cell *cell, char dc, int atk, int def, int hp):
	Character(cell, dc, atk, def, hp){}

void Enemy::notify() {
	#ifdef DEBUG
	cout << "Enemy: notify called" << endl; 
	#endif
	//check block radius for player to fight
	Player *player = cell->findPlayerInBounds();
	if(player != NULL){
		fight(player);
		return;
	}
	move();
}

void Enemy::fight(Entity *against){
	;//TODO: fill in this fight function
}

//TODO: fill in all these for the special subclasses
void Enemy::specialFightEffect(Character *against, int damageDone){
	;
}
