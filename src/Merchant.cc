#include "Merchant.h"
#include "Cell.h"
#include "Entity.h"
#include "Player.h"

bool Merchant::hostile = false;

void Merchant::makeHostile(){
	Merchant::hostile = true;
}

Merchant::Merchant(Cell *cell) :
	Enemy(cell,'M',70,5,30) {}

Merchant::~Merchant() {

}

void Merchant::fight(Entity *against) {
    Enemy::fight(against);
}

bool Merchant::notify(){
	if(HP <= 0){
		this->onDeath();
		return false;
	}
	//Merchants will only attack the player if they're hostile
	if(Merchant::hostile){
		Player *player = cell->findPlayerInBounds();
		if(player != NULL){
			fight(player);
		}
		else
			move();
	}
	else
		move();
	return true;

}
