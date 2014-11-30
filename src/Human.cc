#include "Human.h"
#include "Cell.h"
#include "Entity.h"

Human::Human(Cell *cell):
	Enemy(cell, 'H', 20, 20, 140){}


Human::~Human() {
	
}

void Human::fight(Entity *against) {
    Enemy::fight(against);
}

