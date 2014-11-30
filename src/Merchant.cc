#include "Merchant.h"
#include "Cell.h"
#include "Entity.h"

bool Merchant::hostile = false;

Merchant::Merchant(Cell *cell) :
	Enemy(cell,'M',70,5,30) {}

Merchant::~Merchant() {

}

void Merchant::fight(Entity *against) {
    Enemy::fight(against);
}
