#include "NormalTreasure.h"
#include "Display.h"
#include "Player.h"
#include <sstream>
using namespace std;

NormalTreasure::NormalTreasure(Cell *cell, int value):
	Treasure(cell,
			// either it's a small hoard (7) or a normal hoard (6)
			 value < 2 ? '7' : '6',
			 value){}

bool NormalTreasure::collect(Player *player){ // TODO: remove gold from map after being picked up (I don't think it's done already...)
	player->addGold(value);
    ostringstream ss;
    ss << "Player picked up " << value << " gold. ";
    Display::statusMessage+= ss.str();
	return true;
}
