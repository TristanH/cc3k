#include "HealthPotion.h"

HealthPotion::HealthPotion(Cell *cell, int amount):
	Potion(cell,
		   amount > 0 ? '0' : '3',
		   amount){}

bool HealthPotion::collect(Player *player){
	;//add decorator to player here, fuck if i know how
}