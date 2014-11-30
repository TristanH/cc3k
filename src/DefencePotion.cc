#include "DefencePotion.h"
#include "Player.h"

DefencePotion::DefencePotion(Cell *cell, int amount):
	Potion(cell,
		   amount > 0 ? '2' : '5',
		   amount){}

bool DefencePotion::collect(Player *player){
    Player::addPotion(getDisplayChar(), amount);
    return true;
}