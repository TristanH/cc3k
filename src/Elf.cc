#include "Elf.h"
#include "Cell.h"
#include "Entity.h"
#include "Drow.h"
#include "Display.h"

#include <math.h>

Elf::Elf(Cell* cell):
	Enemy(cell, 'E', 30, 10, 140){}

Elf::~Elf() {

}

void Elf::fight(Entity *against) {
    Enemy::fight(against);
}

int Elf::specialFightEffect(Character *against, int damageDone){
	Drow *drow = dynamic_cast<Drow*>(against);
	if(drow){
		// elf has no special effects if it's fighting a drow 
		return damageDone;
	}
    int secondDamage = ceil((100.0/(100 + against->getDefence()))*this->getAttack());
    Display::statusMessage+="E attacks the Player twice, extra damage added. ";

}

