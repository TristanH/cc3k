#include "Enemy.h"
#include "Cell.h"
#include "Player.h"
#include "PRNG.h"
#include "Display.h"
#include "Goblin.h"
#include <math.h>
#include <sstream>

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
	Character *cAgainst = dynamic_cast<Character*>(against);

    if(!cAgainst){
    	#ifdef DEBUG
        cerr << "Bug: Enemy tried to fight non-character!! returning" << endl;
        #endif
        return;
    }

	bool missAttack = PRNG::random(1) == 1;
	int damage = 0;
	if(missAttack){
		Display::statusMessage+= displayChar;
		Display::statusMessage+= " missed its attack, ";
	}
	else{
    	damage = ceil((100.0/(100 + cAgainst->getDefence()))*this->getAttack());
	}
    damage = specialFightEffect(cAgainst, damage);

    stringstream ss;
    ss << displayChar << " dealt " << damage << " to Player! ";
    Display::statusMessage+= ss.str();
    cAgainst->changeHP(-damage);
    //specialFightEffect is used so subclasses can have their special powers in combat
}

//TODO: fill in all these for the special subclasses
int Enemy::specialFightEffect(Character *against, int damageDone){
	return damageDone;
}

//TODO: override this for dragons, merchants, humans to give more gold
void Enemy::onDeath(){
	Display::statusMessage+=displayChar;
	Display::statusMessage+=" has been killed! ";

	cell->setEntity(NULL);
	int goldSize = PRNG::random(1);
	if(goldSize == 0){
		Display::statusMessage+="Player gained 1 gold! ";
		Player::getInstance()->addGold(1);
	}
	else{
		Display::statusMessage+="Player gained 2 gold! ";
		Player::getInstance()->addGold(2);
	}
    if(Player::getInstance()->raceStr() == "Goblin") {
        Display::statusMessage+="Player steals additional 5 gold. ";
        Player::getInstance()->addGold(5);
    }
}
