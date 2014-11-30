#include "Human.h"
#include "Cell.h"
#include "Entity.h"
#include "Display.h"
#include "Player.h"
#include "Goblin.h"

Human::Human(Cell *cell):
	Enemy(cell, 'H', 20, 20, 140){}


Human::~Human() {
	
}

void Human::fight(Entity *against) {
    Enemy::fight(against);
}

void Human::onDeath(){
	Display::statusMessage+=displayChar;
	Display::statusMessage+=" has been killed! ";

	cell->setEntity(NULL);
	Display::statusMessage+= "Human drops 2 normal piles of gold..";
	Display::statusMessage+="Player gained 4 gold! ";
	Player::getInstance()->addGold(4);

    if(dynamic_cast<Goblin *>(Player::getInstance())) {
        Display::statusMessage+="Player steals additional 5 gold. ";
        Player::getInstance()->addGold(5);
    }
}


