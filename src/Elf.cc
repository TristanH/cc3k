#include "Elf.h"
#include "Cell.h"
#include "Entity.h"
#include "Drow.h"
#include "Display.h"

#include <math.h>
#include <iostream>

using namespace std;

Elf::Elf(Cell* cell):
	Enemy(cell, 'E', 30, 10, 140){}

Elf::~Elf() {

}

void Elf::fight(Entity *against){
	Character *cAgainst = dynamic_cast<Character*>(against);

    if(!cAgainst){
    	cerr << "BUG: elf tries to fight non-character";
        return;
    }

	Drow *drow = dynamic_cast<Drow*>(cAgainst);
	if(drow){
		Display::statusMessage+="E attacks the Player once because it's a Drow: ";
		// elf has no special effects if it's fighting a drow 
		Enemy::fight(against);
	}
    else{
    	Display::statusMessage+="E attacks the Player twice: ";
    	Enemy::fight(against);
    	Enemy::fight(against);
    }

}

