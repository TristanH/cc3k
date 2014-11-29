#include "DefencePotion.h"

DefencePotion::DefencePotion(Cell *cell, int amount):
	Potion(cell,
		   amount > 0 ? '2' : '5',
		   amount){}

bool DefencePotion::collect(Player *player){
	;//add decorator to player here, fuck if i know how
}