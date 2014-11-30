#include "DefencePotion.h"
#include "Player.h"
#include "Display.h"
#include <sstream>
using namespace std;

DefencePotion::DefencePotion(Cell *cell, int amount):
	Potion(cell,
		   amount > 0 ? '2' : '5',
		   amount){}

bool DefencePotion::collect(Player *player){
    Potion::collect(player);
    ostringstream ss;
    ss << "Player used a ";
    if(amount > 0)
        ss << "positive defence potion (+" << amount << " Def). ";
    else
        ss << "negative defence potion (" << amount << " Def). ";
    Display::statusMessage+= ss.str();
    Potion::setPotionsVisible(this->getMapChar());
    return true;
}