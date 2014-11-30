#include "Enemy.h"
#include "Cell.h"
#include "Player.h"
#include "PRNG.h"

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
	//cout << "Enemy: " << *this << ": " << tryDirection << endl;
	#endif
}

Enemy::Enemy(Cell *cell, char dc, int atk, int def, int hp):
	Character(cell, dc, atk, def, hp){}

bool Enemy::notify() {
	#ifdef DEBUG
	//cout << "Enemy: notify called" << endl; 
	#endif
	if(HP <= 0){
		this->onDeath();
		return false;
	}
	//check block radius for player to fight
	Player *player = cell->findPlayerInBounds();
	if(player != NULL){
		fight(player);
		return true;
	}
	move();
	return true;
}

void Enemy::fight(Entity *against){
	;//TODO: fill in this fight function
}

//TODO: fill in all these for the special subclasses
void Enemy::specialFightEffect(Character *against, int damageDone){
	;
}

//TODO: override this for dragons, merchants, humans to give more gold
void Enemy::onDeath(){
	#ifdef DEBUG
	cout << "Enemy killed, onDeath called" << endl;
	#endif
	//cell->setEntity(NULL);
	int goldSize = PRNG::random(1);
	if(goldSize == 0)
		Player::getInstance()->addGold(1);
	else
		Player::getInstance()->addGold(2);
}