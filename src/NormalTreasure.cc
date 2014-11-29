#include "NormalTreasure.h"

#include "Player.h"

NormalTreasure::NormalTreasure(Cell *cell, int value):
	Treasure(cell,
			// either it's a small hoard (7) or a normal hoard (6)
			 value < 2 ? '7' : '6',
			 value){}

bool NormalTreasure::collect(Player *player){
	player->addGold(value);
	// TODO: delete gold from map here
	return true;
}
