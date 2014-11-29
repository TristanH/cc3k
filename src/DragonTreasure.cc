#include "DragonTreasure.h"

#include "Player.h"
#include "Dragon.h"

DragonTreasure::DragonTreasure(Cell *cell, int value, Dragon *dragon):
	Treasure(cell, '8', value), dragon(dragon){

	}

bool DragonTreasure::collect(Player *player){
	if(dragon){
		//TODO: dragon->makeAggresive
		return false;
	}
	else{
		player->addGold(value);
		// TODO: delete gold from map here
		return true;
	}
}

Dragon* DragonTreasure::getDragon(){
	return dragon;
}