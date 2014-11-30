#include "AttackPotion.h"
#include "Player.h"
#include "Display.h"
#include <sstream>
using namespace std;

AttackPotion::AttackPotion(Cell *cell, int amount):
	Potion(cell,
	       amount > 0 ? '1' : '4',
	       amount){}

bool AttackPotion::collect(Player *player){
    Potion::collect(player);
    ostringstream ss;
    ss << "Player used a ";
    if(amount > 0)
        ss << "positive attack potion (+" << amount << " Atk). ";
    else
        ss << "negative attack potion (" << amount << " Atk). ";
    Display::statusMessage+= ss.str();
    return true;
}