#include "HealthPotion.h"
#include "Drow.h"
#include "Display.h"
#include <sstream>
using namespace std;

HealthPotion::HealthPotion(Cell *cell, int amount):
	Potion(cell,
		   amount > 0 ? '0' : '3',
		   amount){}

bool HealthPotion::collect(Player *player){
    if(dynamic_cast<Drow *>(Player::getInstance())) amount *= 1.5;
	Player::addPotion(getDisplayChar(), amount);
    ostringstream ss;
    ss << "Player used a ";
    if(amount > 0)
        ss << "positive health potion (+" << amount << " HP). ";
    else
        ss << "negative health potion (" << amount << " HP). ";
    Display::statusMessage+= ss.str();
    return true;
}