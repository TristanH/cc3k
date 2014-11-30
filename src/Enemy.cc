#include "Enemy.h"
#include "Cell.h"
#include "Player.h"
#include "PRNG.h"
#include "Display.h"

#include <math.h>

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

}

Enemy::Enemy(Cell *cell, char dc, int atk, int def, int hp):
	Character(cell, dc, atk, def, hp){}

bool Enemy::notify() {
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
	bool missAttack = PRNG::random(1) == 1;
	if(missAttack){
		Display::statusMessage+= displayChar;
		Display::statusMessage+= " missed its attack on Player! ";
		return;
	}

	Character *cAgainst = dynamic_cast<Character*>(against);

    if(!cAgainst){
    	// should never get here since fight is always called with player
        #ifdef DEBUG
        cout << "Bug: Enemy tried to fight non-character!! returning" << endl;
        #endif
        return;
    }
    
    int damage = ceil((100.0/(100 + cAgainst->getDefence()))*this->getAttack());
    cAgainst->changeHP(-damage);
    #ifdef DEBUG
    cout << "Enemy dealt " << damage << " damage. " << endl;
    // TODO: status message here
    #endif
    //specialFightEffect is used so subclasses can have their special powers in combat
    specialFightEffect(cAgainst, damage);
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
	cell->setEntity(NULL);
	int goldSize = PRNG::random(1);
	if(goldSize == 0)
		Player::getInstance()->addGold(1);
	else
		Player::getInstance()->addGold(2);
}
