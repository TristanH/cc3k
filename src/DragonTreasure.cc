#include "DragonTreasure.h"
#include "Display.h"
#include "Player.h"
#include "Dragon.h"

DragonTreasure::DragonTreasure(Cell *cell, int value, Dragon *dragon):
	Treasure(cell, '8', value), dragon(dragon){

	}

bool DragonTreasure::collect(Player *player){
	if(dragon){
		//TODO: dragon->makeAggresive
		Display::statusMessage += "PC has angered the dragon";
		return false;
	}
	else{
		player->addGold(value);
		return true;
	}
}

Dragon* DragonTreasure::getDragon(){
	return dragon;
}