#include "Orc.h"
#include "Cell.h"
#include "Entity.h"
#include "Goblin.h"
#include "Display.h"

#include <math.h>

Orc::Orc(Cell *cell) : 
	Enemy(cell,'O',30,25,180) {}

Orc::~Orc() {

}

void Orc::fight(Entity *against) {
    Enemy::fight(against);
}

int Orc::specialFightEffect(Character *against, int damageDone){
	Goblin *goblin = dynamic_cast<Goblin*>(against);
	if(goblin){
		Display::statusMessage+="O does 50% more damage because Player is a goblin: ";
		return floor(damageDone*1.5);
	}
	else
		return damageDone;
}