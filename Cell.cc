#include "Cell.h"
#include "Map.h"
#include "PRNG.h"

#include <ctime>

using namespace std;

Cell::Cell(int r, int c, char type, Floor *floor, Entity *entity = NULL): 
	(r), c(c), type(type), floor(floor), entity(entity) {}

//make this const?
Cell::directions[] = {"no", "ne", "ea", "se", "so", "sw", "we", "nw"};

void Cell::notifyFloor(){
	floor->notify(i,j,entity);
}

void Cell::setEntity(const Entity *newEntity){
	entity = newEntity;
	notifyFloor();
}

Entity* Cell::getEntity(){
	return entity;
}

bool Cell::isWalkable(){
	// what about the case where the entity is gold?
	// technically you are supposed to walk onto gold to pick it up but we can fake this.
	// same goes for potions.
	return (type == '.' || type == '#' || type == '+') && entity == NULL;
}

char Cell::getType(){
	return type;
}

Cell* Cell::getAdjacentCell(string direction){
	if(direction == "no")
		return Floor.getCell(y-1,x);
	else if(direction == "ne")
		return Floor.getCell(y-1, x+1);
	else if(direction == "ea")
		return Floor.getCell(y, x+1);
	else if(direction == "se")
		return Floor.getCell(y+1, x+1);
	else if(direction == "so")
		return Floor.getCell(y+1, x);
	else if(direction == "sw")
		return Floor.getCell(y+1, x-1);
	else if(direction == "we")
		return Floor.getCell(y, x-1);
	else if(direction == "nw")
		return Floor.getCell(y-1, x-1);

	cerr << "ERROR: Invalid direciton given to getAdjacentCell" << endl;
	return NULL;
}

Player* Cell::findPlayerInBounds(){
	for(int i=0;i<7;i++){
		Cell *checkCell = getAdjacentCell(directions[i]);
		if(*checkCell.getEntity() == Player.getInstance())
			return checkCell.getEntity();
	}
	// return NULL if the player's not in a block radius
	return NULL;
}

string Cell::getRandomDirection(){
	prng random(time(NULL));
	return directions[random(7)];
}


