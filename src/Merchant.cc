#include "Merchant.h"
#include "Cell.h"
#include "Entity.h"
#include "Player.h"
#include "Display.h"
#include "Goblin.h"

bool Merchant::hostile = false;

void Merchant::makeHostile(){
	Display::statusMessage+= " Merchants are now aggressive! ";
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

void Merchant::onDeath(){
	Display::statusMessage+="M has been killed! ";
	cell->setEntity(NULL);

	Display::statusMessage+="Player gained 4 gold! ";
	Player::getInstance()->addGold(4);

    if(Player::getInstance()->raceStr() == "Goblin") {
        Display::statusMessage+="Player steals additional 5 gold. ";
        Player::getInstance()->addGold(5);
    }
}
