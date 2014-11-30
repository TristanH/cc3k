#include "AttackPotion.h"
#include "Player.h"

AttackPotion::AttackPotion(Cell *cell, int amount):
	Potion(cell,
	       amount > 0 ? '1' : '4',
	       amount){}

bool AttackPotion::collect(Player *player){
	Player::addPotion(getDisplayChar(), amount);
    return true;
}