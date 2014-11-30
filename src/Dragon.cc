#include "Dragon.h"
#include "Cell.h"
#include "Player.h"
#include "DragonTreasure.h"

Dragon::Dragon(Cell *cell):
	Enemy(cell, 'D', 20, 20, 150), treasure(NULL){}

Dragon::~Dragon() {
	
}

void Dragon::fight(Entity *against) {

}

bool Dragon::notify() {
	if(HP <= 0){
		Enemy::onDeath();
		treasure->dragonDead();
		return false;
	}
	if(hostile){
		fight(Player::getInstance());
	}
	return true;
}

void Dragon::makeHostile(){
	hostile = true;
}

void Dragon::setTreasure(DragonTreasure* dt){
	treasure = dt;
}