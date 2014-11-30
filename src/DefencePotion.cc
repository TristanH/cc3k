#include "DefencePotion.h"
#include "Player.h"
#include "Drow.h"
#include "Display.h"
#include <sstream>
using namespace std;

DefencePotion::DefencePotion(Cell *cell, int amount):
	Potion(cell,
		   amount > 0 ? '2' : '5',
		   amount){}

bool DefencePotion::collect(Player *player){
    if(dynamic_cast<Drow *>(Player::getInstance())) amount *= 1.5;
    Player::addPotion(getMapChar(), amount);
    ostringstream ss;
    ss << "Player used a ";
    if(amount > 0)
        ss << "positive defence potion (+" << amount << " Def). ";
    else
        ss << "negative defence potion (" << amount << " Def). ";
    Display::statusMessage+= ss.str();
    return true;
}