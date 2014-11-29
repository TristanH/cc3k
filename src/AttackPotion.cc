#include "AttackPotion.h"

AttackPotion::AttackPotion(Cell *cell, int amount):
	Potion(cell,
	       amount > 0 ? '1' : '4',
	       amount
		   ){}

bool AttackPotion::collect(Player *player){
	;//add decorator to player here, fuck if i know how
}