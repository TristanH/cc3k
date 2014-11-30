#include "HealthPotion.h"
#include "Display.h"
#include <sstream>
using namespace std;

HealthPotion::HealthPotion(Cell *cell, int amount):
	Potion(cell,
		   amount > 0 ? '0' : '3',
		   amount){}

bool HealthPotion::collect(Player *player){
    Potion::collect(player);
    ostringstream ss;
    ss << "Player used a ";
    if(amount > 0)
        ss << "positive health potion (+" << amount << " HP). ";
    else
        ss << "negative health potion (" << amount << " HP). ";
    Display::statusMessage+= ss.str();
    Potion::setPotionsVisible(this->getMapChar());
    return true;
}