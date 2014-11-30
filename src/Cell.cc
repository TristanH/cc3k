#include "Cell.h"
#include "Floor.h"
#include "PRNG.h"
#include "Player.h"

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

Cell::Cell(int r, int c, char type, Floor *floor, Entity *entity): 
	r(r), c(c), type(type), floor(floor), entity(entity) {}

//make this const?
const string Cell::directions[] = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};

bool Cell::stairwayExists = false;

void Cell::notifyFloor(){
	floor->notify(r,c,this);
}

void Cell::setEntity(Entity *newEntity){
	// TODO: if there is an entity here and we wanna move to it for some reason, we should delete that existing entity
	entity = newEntity;
	if(newEntity) entity->setCell(this); // The entity is not NULL (i.e. contains a non floor/wallcl)
	notifyFloor();
}

Entity* Cell::getEntity(){
	return entity;
}

bool Cell::isWalkable(bool allowPassages){
	// what about the case where the entity is gold?
	// technically you are supposed to walk onto gold to pick it up but we can fake this.
	// same goes for potions.
	if(allowPassages) return (type == '.' || type == '#' || type == '+') && entity == NULL;
	else return (type == '.' && entity == NULL);
}

char Cell::getType(){
	return type;
}

int Cell::getR() {
	return r;
}

int Cell::getC() {
	return c;
}

char Cell::getDisplayChar(){
	if(entity==NULL)
		return type;
	else
		return entity->getDisplayChar();
}

// only called once to make this cell the stairway
void Cell::makeStairway(){
	if(Cell::stairwayExists){
		cerr << "Tried to make a cell a stairway when the stairway already exists!! " << endl;
		return;
	}
	type = '\\';
	Cell::stairwayExists = true;
	floor->notify(r,c,this);

}

Cell* Cell::getAdjacentCell(string direction){
	if(direction == "no")
		return floor->getCell(r-1,c);
	else if(direction == "ne")
		return floor->getCell(r-1, c+1);
	else if(direction == "ea")
		return floor->getCell(r, c+1);
	else if(direction == "se")
		return floor->getCell(r+1, c+1);
	else if(direction == "so")
		return floor->getCell(r+1, c);
	else if(direction == "sw")
		return floor->getCell(r+1, c-1);
	else if(direction == "we")
		return floor->getCell(r, c-1);
	else if(direction == "nw")
		return floor->getCell(r-1, c-1);

	cerr << "ERROR: Invalid direciton given to getAdjacentCell" << endl;
	return NULL;
}

Player* Cell::findPlayerInBounds(){
	for(int i=0;i<7;i++){
		Cell *checkCell = getAdjacentCell(directions[i]);
		if(checkCell->getEntity() == Player::getInstance()) {
			Entity *checkEntity = checkCell->getEntity();
			Player *thePlayer = dynamic_cast<Player *>(checkEntity);
			if(thePlayer) {
				return thePlayer;
			} else {
				cerr << "Error in dynamic_cast from Entity* to Player* in Cell::findPlayerInBounds" << endl;
			}
		}
	}
	// return NULL if the player's not in a block radius
	return NULL;
}

Cell* Cell::findNearbyEmpty(){
	// start at a random direction so we dont always spawn dragons north of their treasures
	int startI = PRNG::random(7);
	int atI = startI;
	do{
		Cell *cell = getAdjacentCell(directions[atI]);
		if(cell->isWalkable())
			return cell;
		atI++;
		if(atI == 8)
			atI = 0;

	} while(startI != atI);

	return NULL;
}

string Cell::getRandomDirection(){
	return directions[PRNG::random(7)];
}

bool Cell::isValidDirection(string direction){
	for(int i=0; i < 8; i++){
		if(direction == Cell::directions[i])
			return true;
	}
	return false;

}


