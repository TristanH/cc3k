#include "DragonTreasure.h"
#include "Display.h"
#include "Player.h"
#include "Dragon.h"

DragonTreasure::DragonTreasure(Cell *cell, int value, Dragon *dragon):
	Treasure(cell, '8', value), dragon(dragon){
		if(dragon)
			dragon->setTreasure(this);
	}

bool DragonTreasure::collect(Player *player){
	if(dragon){
		Display::statusMessage += "Player has angered the dragon! ";
		dragon->makeHostile();
		return false;
	}
	else{
		Display::statusMessage+= "Collected dragon hoard! ";
		player->addGold(value);
		return true;
	}
}

Dragon* DragonTreasure::getDragon(){
	return dragon;
}

void DragonTreasure::dragonDead(){
	// don't point at soon to be deallocated memory
	// also now let this treasure be collected
	dragon = NULL;
}

void DragonTreasure::setDragon(Dragon *d){
	dragon = d;
}